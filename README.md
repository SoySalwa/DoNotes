# DoNotes

**DoNotes** is a lightweight note-taking application written in C++ using **Qt6**. It supports multiple tabs, basic file operations (load/save), and shows word/character counts in real time.

## Features

- Multi-tab text editor.
- Save notes as `.txt` or `.doNote` files.
- Load existing notes from disk.
- Word and character count displayed in the status bar.
- New note creation via a dedicated button.
- Notes are stored in `data/notes/` by default.

## Requirements

- **C++17** compiler (GCC, Clang, or MSVC)
- **CMake** 3.10 or higher
- **Qt6** (Core and Widgets modules)

## Project Structure

```
DoNotes/
├── CMakeLists.txt
├── src/
│   ├── app.cc
│   └── ui/
│       ├── MainWindow.cc
│       └── MainWindow.h
└── data/
    └── notes/       # Default folder to store notes
```

## CMake Build Instructions

1. **Clone the repository** (or copy files):

```bash
git clone https://github.com/SoySalwa/DoNotes.git
cd DoNotes
```

2. **Create a build directory**:

```bash
mkdir build
cd build
```

3. **Configure the project using CMake**:

```bash
cmake ..
```

This will detect Qt6 and configure the project. Make sure your `CMAKE_PREFIX_PATH` includes the path to your Qt6 installation if CMake cannot find it automatically.

4. **Build the project**:

```bash
cmake --build .
```

5. **Run the executable**:

```bash
./DoNotes   # Linux/macOS
```

## Notes

- All notes are stored in `data/notes/`. The application automatically creates this folder if it does not exist.
- The “+” button next to the tabs allows you to create new notes.
- Word and character counts are updated in real-time in the status bar.

## Dependencies

- **Qt6::Core**
- **Qt6::Widgets**

These are required for UI components, file handling, and signals/slots.

## License

Specify your license here (MIT, GPL, etc.).
