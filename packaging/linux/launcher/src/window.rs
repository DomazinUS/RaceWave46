//! The first-run window: an Adwaita status page with one action.

use adw::prelude::*;
use gtk::{gio, glib};

use crate::game::{Game, ImportStatus};
use crate::text;

/// Application ID; the Flatpak manifest may override it at build time.
pub const APP_ID: &str = match option_env!("RACEWAVE46_APP_ID") {
    Some(id) => id,
    None => "io.github.DomazinUS.RaceWave46",
};

#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum Startup {
    NeedsRom,
    GameMissing,
    StartFailed,
}

pub fn run(game: Game, startup: Startup) -> glib::ExitCode {
    let application = adw::Application::builder().application_id(APP_ID).build();
    application.connect_activate(move |application| {
        if let Some(window) = application.active_window() {
            window.present();
            return;
        }
        build(application, game.clone(), startup);
    });
    // The game's own options were consumed in main; GTK gets none of them.
    application.run_with_args::<&str>(&[])
}

struct Page {
    window: adw::ApplicationWindow,
    status: adw::StatusPage,
    button: gtk::Button,
    spinner: adw::Spinner,
}

fn build(application: &adw::Application, game: Game, startup: Startup) {
    let status = adw::StatusPage::builder()
        .icon_name(APP_ID)
        .title(text::HEADING)
        .description(text::DESCRIPTION)
        .build();
    let button = gtk::Button::builder()
        .label(text::SELECT_ROM)
        .halign(gtk::Align::Center)
        .css_classes(["suggested-action", "pill"])
        .build();
    let spinner = adw::Spinner::builder()
        .visible(false)
        .width_request(32)
        .height_request(32)
        .build();
    let actions = gtk::Box::new(gtk::Orientation::Vertical, 12);
    actions.append(&button);
    actions.append(&spinner);
    status.set_child(Some(&actions));

    let toolbar = adw::ToolbarView::new();
    toolbar.add_top_bar(&adw::HeaderBar::new());
    toolbar.set_content(Some(&status));
    let window = adw::ApplicationWindow::builder()
        .application(application)
        .title(text::WINDOW_TITLE)
        .default_width(560)
        .default_height(520)
        .content(&toolbar)
        .build();

    match startup {
        Startup::NeedsRom => {}
        Startup::GameMissing => {
            status.set_icon_name(Some("dialog-error-symbolic"));
            status.set_description(Some(text::GAME_MISSING));
            button.set_visible(false);
        }
        Startup::StartFailed => status.set_description(Some(text::START_FAILED)),
    }

    let page = std::rc::Rc::new(Page {
        window: window.clone(),
        status,
        button: button.clone(),
        spinner,
    });
    button.connect_clicked(move |_| {
        let page = page.clone();
        let game = game.clone();
        glib::spawn_future_local(async move { choose_rom(&page, game).await });
    });
    window.present();
}

async fn choose_rom(page: &Page, game: Game) {
    let filter = gtk::FileFilter::new();
    filter.set_name(Some(text::ROM_FILTER));
    filter.add_mime_type("application/x-n64-rom");
    for suffix in ["z64", "n64", "v64"] {
        filter.add_suffix(suffix);
    }
    let filters = gio::ListStore::new::<gtk::FileFilter>();
    filters.append(&filter);
    let dialog = gtk::FileDialog::builder()
        .title(text::DIALOG_TITLE)
        .modal(true)
        .filters(&filters)
        .default_filter(&filter)
        .build();
    // Inside Flatpak this is the FileChooser portal; the chosen file is
    // exposed through the document portal without broader file access.
    let Ok(file) = dialog.open_future(Some(&page.window)).await else {
        return;
    };
    let Some(path) = file.path() else {
        show_error(page, ImportStatus::FailedToOpen);
        return;
    };

    set_busy(page, true);
    let importer = game.clone();
    let result = gio::spawn_blocking(move || importer.import_rom(&path)).await;
    set_busy(page, false);
    match result {
        Ok(Ok(ImportStatus::Good)) => {
            let error = game.exec();
            eprintln!("[launcher] cannot start {}: {error}", game.path().display());
            page.status.set_description(Some(text::START_FAILED));
        }
        Ok(Ok(status)) => show_error(page, status),
        Ok(Err(error)) => {
            eprintln!("[launcher] cannot run {}: {error}", game.path().display());
            show_error(page, ImportStatus::OtherError);
        }
        Err(_) => show_error(page, ImportStatus::OtherError),
    }
}

fn set_busy(page: &Page, busy: bool) {
    page.button.set_sensitive(!busy);
    page.button
        .set_label(if busy { text::IMPORTING } else { text::SELECT_ROM });
    page.spinner.set_visible(busy);
}

fn show_error(page: &Page, status: ImportStatus) {
    let dialog = adw::AlertDialog::new(Some(text::IMPORT_FAILED_HEADING), Some(text::import_error(status)));
    dialog.add_response("close", text::CLOSE);
    dialog.set_default_response(Some("close"));
    dialog.present(Some(&page.window));
}
