"""Compile the actual RT64 filter lifecycle without constructing a renderer."""
from pathlib import Path
import re
import sys

root, output = map(Path, sys.argv[1:3])
directory = root / "lib/rt64/src/hle"
source = (directory / "rt64_application_window.cpp").read_text()
header = (directory / "rt64_application_window.h").read_text()
application = (directory / "rt64_application.cpp").read_text()


def block(text, start):
    opening = text.index("{", start)
    depth = 1
    end = opening + 1
    while depth:
        depth += (text[end] == "{") - (text[end] == "}")
        end += 1
    return text[start:end]


fields = []
for name in ("listener", "sdlWindow", "sdlEventFilterStored", "sdlEventFilterUserdata",
             "sdlEventFilterInstalled", "eventFilterMutex", "eventFiltersStopped"):
    matches = re.findall(r"^\s*[^/\n;()]+\b" + name + r"\b[^;\n]*;", header, re.M)
    assert len(matches) == 1, name
    fields.append(matches[0].strip())
listener = block(header, header.index("struct Listener {")) + ";"
methods = []
for signature in ("void ApplicationWindow::sdlCheckFilterInstallation()",
                  "void ApplicationWindow::stopEventFilters()",
                  "int ApplicationWindow::sdlEventFilter(",
                  "void ApplicationWindow::windowMessage("):
    methods.append(block(source, source.index(signature)))
end = block(application, application.index("void Application::end()"))
assert end.index("appWindow->stopEventFilters();") < end.index("state.reset();"), \
    "Renderer state must remain alive until filter shutdown completes"
destructor = block(source, source.index("ApplicationWindow::~ApplicationWindow()"))
assert "stopEventFilters();" in destructor, "Destructor lost the filter shutdown fallback"
output.write_text("\n".join([
    "namespace RT64 {", "struct ApplicationWindow {", listener, *fields,
    "void sdlCheckFilterInstallation();", "void stopEventFilters();",
    "static int sdlEventFilter(void*, SDL_Event*);",
    "void windowMessage(UINT, WPARAM, LPARAM);", "};", *methods, "}",
]))
