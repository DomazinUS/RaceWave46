//! RaceWave46 launcher for Linux.
//!
//! When the game already holds a valid ROM, this process is replaced by the
//! game straight away and no window is shown. Otherwise a small Adwaita window
//! asks for the player's ROM through the FileChooser portal, has the game
//! import it, and then starts the game.

mod game;
mod text;
mod window;

use std::path::PathBuf;

use game::Game;
use gtk::glib;
use window::Startup;

fn main() -> glib::ExitCode {
    let launcher = std::env::current_exe().unwrap_or_else(|_| PathBuf::from("racewave46"));
    let arguments = std::env::args_os().skip(1).collect();
    let game = Game::new(Game::locate(&launcher, std::env::var_os(game::GAME_ENV)), arguments);

    let startup = match game.has_valid_rom() {
        Ok(true) => {
            let error = game.exec();
            eprintln!("[launcher] cannot start {}: {error}", game.path().display());
            Startup::StartFailed
        }
        Ok(false) => Startup::NeedsRom,
        Err(error) => {
            eprintln!("[launcher] cannot run {}: {error}", game.path().display());
            Startup::GameMissing
        }
    };
    window::run(game, startup)
}
