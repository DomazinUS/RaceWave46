//! User-facing text for the launcher window.

use crate::game::ImportStatus;

pub const WINDOW_TITLE: &str = "RaceWave46";
pub const HEADING: &str = "Welcome to RaceWave46";
pub const DESCRIPTION: &str = "To play, select your own copy of Wave Race 64 (USA, Rev 1). It is checked and copied into RaceWave46's private data, and you only need to do this once.";
pub const SELECT_ROM: &str = "Select ROM…";
pub const IMPORTING: &str = "Checking ROM…";
pub const DIALOG_TITLE: &str = "Select Wave Race 64 ROM";
pub const ROM_FILTER: &str = "Nintendo 64 ROMs";
pub const IMPORT_FAILED_HEADING: &str = "This ROM Can’t Be Used";
pub const GAME_MISSING: &str = "The game files are missing. Reinstall RaceWave46.";
pub const START_FAILED: &str = "The game could not be started.";
pub const CLOSE: &str = "Close";

/// Explains a rejected ROM. Mirrors the in-game launcher's messages.
pub fn import_error(status: ImportStatus) -> &'static str {
    use ImportStatus::*;
    match status {
        FailedToOpen => "The file could not be opened.",
        NotARom => "This is not a Nintendo 64 ROM file.",
        IncorrectRom => "This ROM is not Wave Race 64.",
        NotYet => "This game isn’t supported yet.",
        IncorrectVersion => {
            "This is Wave Race 64, but the wrong version. RaceWave46 requires the unmodified USA Rev 1 release."
        }
        Good | OtherError => "An unknown error has occurred.",
    }
}
