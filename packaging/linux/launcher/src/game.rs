//! The game executable's ROM setup interface (`--check-rom` and
//! `--import-rom`). All validation, byte-order normalisation and patching stay
//! in the game; this module only runs it and reads its single status line.

use std::ffi::OsString;
use std::io;
use std::os::unix::process::CommandExt;
use std::path::{Path, PathBuf};
use std::process::{Command, Stdio};

/// Environment override for the game executable, mainly for development.
pub const GAME_ENV: &str = "RACEWAVE46_GAME";
/// File name of the game executable produced by the CMake build.
pub const GAME_NAME: &str = "WaveRace64Recompiled";

#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum ImportStatus {
    Good,
    FailedToOpen,
    NotARom,
    IncorrectRom,
    NotYet,
    IncorrectVersion,
    OtherError,
}

impl ImportStatus {
    /// Parses the `status=<token>` line the game prints on stdout.
    pub fn parse(output: &str) -> Self {
        match status_token(output) {
            Some("good") => Self::Good,
            Some("failed-to-open") => Self::FailedToOpen,
            Some("not-a-rom") => Self::NotARom,
            Some("incorrect-rom") => Self::IncorrectRom,
            Some("not-yet") => Self::NotYet,
            Some("incorrect-version") => Self::IncorrectVersion,
            _ => Self::OtherError,
        }
    }
}

fn status_token(output: &str) -> Option<&str> {
    output
        .lines()
        .rev()
        .find_map(|line| line.trim().strip_prefix("status="))
}

#[derive(Debug, Clone)]
pub struct Game {
    path: PathBuf,
    arguments: Vec<OsString>,
}

impl Game {
    pub fn new(path: PathBuf, arguments: Vec<OsString>) -> Self {
        Self { path, arguments }
    }

    /// Finds the game: `$RACEWAVE46_GAME`, else beside this launcher, else in
    /// `../lib/racewave46/` (the installed layout, which keeps the game's
    /// `assets` directory out of `bin`).
    pub fn locate(launcher: &Path, override_path: Option<OsString>) -> PathBuf {
        if let Some(path) = override_path.filter(|path| !path.is_empty()) {
            return PathBuf::from(path);
        }
        let sibling = launcher.with_file_name(GAME_NAME);
        let installed = launcher
            .parent()
            .and_then(Path::parent)
            .map(|prefix| prefix.join("lib").join("racewave46").join(GAME_NAME));
        match installed {
            Some(installed) if !sibling.exists() && installed.exists() => installed,
            _ => sibling,
        }
    }

    pub fn path(&self) -> &Path {
        &self.path
    }

    /// True only when the game reports a stored ROM that passes its hash check.
    pub fn has_valid_rom(&self) -> io::Result<bool> {
        let output = self.setup_command().arg("--check-rom").output()?;
        Ok(output.status.success() && status_token(&String::from_utf8_lossy(&output.stdout)) == Some("valid"))
    }

    pub fn import_rom(&self, rom: &Path) -> io::Result<ImportStatus> {
        let output = self.setup_command().arg("--import-rom").arg(rom).output()?;
        let status = ImportStatus::parse(&String::from_utf8_lossy(&output.stdout));
        // A zero exit status is the game's own confirmation; never report
        // success from the text alone.
        Ok(match status {
            ImportStatus::Good if !output.status.success() => ImportStatus::OtherError,
            other => other,
        })
    }

    /// Replaces this process with the game. Only returns on failure.
    pub fn exec(&self) -> io::Error {
        self.command().args(&self.arguments).exec()
    }

    /// The game loads its interface from `assets/` relative to its working
    /// directory, so every run starts in the game's own directory.
    fn command(&self) -> Command {
        let mut command = Command::new(&self.path);
        if let Some(directory) = self.path.parent().filter(|directory| !directory.as_os_str().is_empty()) {
            command.current_dir(directory);
        }
        command
    }

    fn setup_command(&self) -> Command {
        let mut command = self.command();
        // --runtime-dir must reach the setup run too, so a custom profile
        // checks and receives the same ROM the game will load.
        let mut arguments = self.arguments.iter();
        while let Some(argument) = arguments.next() {
            if argument == "--runtime-dir" {
                command.arg(argument);
                if let Some(value) = arguments.next() {
                    command.arg(absolute(value));
                }
            }
        }
        command.stdin(Stdio::null()).stderr(Stdio::inherit());
        command
    }
}

/// Relative paths given on the command line refer to the caller's directory,
/// not to the game directory the setup run starts in.
fn absolute(value: &OsString) -> OsString {
    let path = Path::new(value);
    if path.is_absolute() {
        return value.clone();
    }
    std::env::current_dir()
        .map(|directory| directory.join(path).into_os_string())
        .unwrap_or_else(|_| value.clone())
}

#[cfg(test)]
mod tests {
    use super::*;
    use std::fs;
    use std::os::unix::fs::PermissionsExt;

    #[test]
    fn parses_every_game_status() {
        let cases = [
            ("status=good\n", ImportStatus::Good),
            ("status=failed-to-open", ImportStatus::FailedToOpen),
            ("status=not-a-rom", ImportStatus::NotARom),
            ("status=incorrect-rom", ImportStatus::IncorrectRom),
            ("status=not-yet", ImportStatus::NotYet),
            ("status=incorrect-version", ImportStatus::IncorrectVersion),
            ("status=other-error", ImportStatus::OtherError),
            ("status=something-new", ImportStatus::OtherError),
            ("", ImportStatus::OtherError),
        ];
        for (output, expected) in cases {
            assert_eq!(ImportStatus::parse(output), expected, "{output:?}");
        }
    }

    #[test]
    fn uses_the_last_status_line() {
        assert_eq!(
            ImportStatus::parse("noise\nstatus=not-a-rom\nstatus=good\n"),
            ImportStatus::Good
        );
    }

    fn scratch(name: &str) -> PathBuf {
        let directory = std::env::temp_dir().join(format!("racewave46-launcher-{name}-{}", std::process::id()));
        let _ = fs::remove_dir_all(&directory);
        fs::create_dir_all(&directory).unwrap();
        directory
    }

    #[test]
    fn locates_game_from_override_sibling_or_installed_layout() {
        let prefix = scratch("locate");
        let launcher = prefix.join("bin").join("racewave46");
        let sibling = prefix.join("bin").join(GAME_NAME);
        let installed = prefix.join("lib").join("racewave46").join(GAME_NAME);
        assert_eq!(
            Game::locate(&launcher, Some("/opt/game".into())),
            Path::new("/opt/game")
        );
        assert_eq!(Game::locate(&launcher, Some("".into())), sibling);
        fs::create_dir_all(installed.parent().unwrap()).unwrap();
        fs::write(&installed, "").unwrap();
        assert_eq!(Game::locate(&launcher, None), installed);
        fs::create_dir_all(sibling.parent().unwrap()).unwrap();
        fs::write(&sibling, "").unwrap();
        assert_eq!(Game::locate(&launcher, None), sibling);
        fs::remove_dir_all(prefix).unwrap();
    }

    /// A stand-in for the game that records its working directory and
    /// arguments, then answers like the game.
    fn mock_game(directory: &Path, body: &str) -> PathBuf {
        let path = directory.join("game");
        let script = format!(
            "#!/bin/sh\npwd > \"{0}/cwd\"\necho \"$@\" >> \"{0}/arguments\"\n{body}\n",
            directory.display()
        );
        fs::write(&path, script).unwrap();
        fs::set_permissions(&path, fs::Permissions::from_mode(0o755)).unwrap();
        path
    }

    #[test]
    fn check_requires_success_and_valid_status() {
        let directory = scratch("check");
        let valid = Game::new(mock_game(&directory, "echo status=valid"), vec![]);
        assert!(valid.has_valid_rom().unwrap());
        let missing = Game::new(mock_game(&directory, "echo status=missing; exit 1"), vec![]);
        assert!(!missing.has_valid_rom().unwrap());
        let inconsistent = Game::new(mock_game(&directory, "echo status=valid; exit 1"), vec![]);
        assert!(!inconsistent.has_valid_rom().unwrap());
        fs::remove_dir_all(directory).unwrap();
    }

    #[test]
    fn import_runs_in_game_directory_and_forwards_runtime_directory_only() {
        let directory = scratch("import");
        let game = Game::new(
            mock_game(&directory, "echo status=good"),
            vec!["--windowed".into(), "--runtime-dir".into(), "/tmp/profile".into()],
        );
        assert_eq!(
            game.import_rom(Path::new("/tmp/my rom.z64")).unwrap(),
            ImportStatus::Good
        );
        let arguments = fs::read_to_string(directory.join("arguments")).unwrap();
        assert_eq!(
            arguments.trim(),
            "--runtime-dir /tmp/profile --import-rom /tmp/my rom.z64"
        );
        let cwd = fs::read_to_string(directory.join("cwd")).unwrap();
        assert_eq!(
            Path::new(cwd.trim()).canonicalize().unwrap(),
            directory.canonicalize().unwrap()
        );
        fs::remove_dir_all(directory).unwrap();
    }

    #[test]
    fn relative_runtime_directory_resolves_from_caller() {
        let directory = scratch("relative");
        let game = Game::new(
            mock_game(&directory, "echo status=valid"),
            vec!["--runtime-dir".into(), "profile".into()],
        );
        assert!(game.has_valid_rom().unwrap());
        let arguments = fs::read_to_string(directory.join("arguments")).unwrap();
        let expected = std::env::current_dir().unwrap().join("profile");
        assert_eq!(
            arguments.trim(),
            format!("--runtime-dir {} --check-rom", expected.display())
        );
        fs::remove_dir_all(directory).unwrap();
    }

    #[test]
    fn import_never_trusts_good_with_failed_exit() {
        let directory = scratch("exit");
        let game = Game::new(mock_game(&directory, "echo status=good; exit 1"), vec![]);
        assert_eq!(game.import_rom(Path::new("rom.z64")).unwrap(), ImportStatus::OtherError);
        let rejected = Game::new(mock_game(&directory, "echo status=incorrect-version; exit 1"), vec![]);
        assert_eq!(
            rejected.import_rom(Path::new("rom.z64")).unwrap(),
            ImportStatus::IncorrectVersion
        );
        fs::remove_dir_all(directory).unwrap();
    }

    #[test]
    fn missing_game_is_an_error() {
        let game = Game::new(PathBuf::from("/nonexistent/racewave46-game"), vec![]);
        assert!(game.has_valid_rom().is_err());
    }
}
