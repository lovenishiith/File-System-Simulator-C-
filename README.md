# 🚀 File System Simulator (C++)

A command-line based **file system simulator** built in C++ that mimics core functionalities of an operating system’s file management system.

This project demonstrates concepts from **data structures, system design, and file handling**, including directory navigation, file operations, persistence, and search.

---

## ✨ Features

### 📂 Directory Operations

* `mkdir` → Create directories
* `rmdir` → Delete directories (recursive)
* `cd` → Navigate directories (supports `/`, `..`, `.`)
* `pwd` → Display current path
* `tree` → Visualize directory structure

---

### 📄 File Operations

* `touch` → Create file
* `write` → Add content to file
* `read` → Read file content
* `rm` → Delete file
* `rename` → Rename file/directory
* `mv` → Move files
* `cp` → Copy files and directories (deep copy)

---

### 🔍 Search

* `find` → Search files by name
* `search` → Search files by content using DFS

---

### 💾 Persistence

* Saves entire file system to disk (`filesystem.txt`)
* Restores structure, content, and metadata on restart

---

### ⏱️ Metadata

Each file tracks:

* Creation time
* Last modified time

---

## 🧠 Concepts Used

* **Data Structures:** N-ary Tree
* **Algorithms:** DFS (Depth First Search), Recursion
* **System Design:** File system simulation
* **File Handling:** `ifstream`, `ofstream`
* **Serialization & Deserialization**
* **Dynamic Memory Management (Pointers)**

---

## ⚙️ Project Structure

```
FileSystem-Simulator/
├── main.cpp
├── filesystem.hpp
├── filesystem.cpp
├── utils.hpp
├── utils.cpp
├── persistence.hpp
├── persistence.cpp
├── README.md
```

---

## ⚙️ How to Run

### Compile:

```bash
g++ main.cpp filesystem.cpp utils.cpp persistence.cpp -o fs
```

### Run (Windows):

```bash
fs.exe
```

### Run (Linux/Mac):

```bash
./fs
```

---

## 📌 Sample Commands

```
mkdir A
mkdir A/B
touch A/B/file.txt
write A/B/file.txt
search hello
tree
```

---

## 🔥 Design Highlights

* Implemented **Linux-like path navigation** (`/`, `..`, `.`) using a path resolution system
* Designed **persistent storage system** using serialization/deserialization
* Built **deep copy mechanism** for accurate file/directory duplication
* Handled **edge cases** like invalid paths and duplicate files
* Modularized code into multiple files for **scalability and maintainability**

---

## 🚧 Limitations

* No file permission system (rwx)
* No multi-user support
* CLI-based (no GUI)

---

## 🚀 Future Improvements

* 🔐 File permission system
* 🔁 Undo / Redo functionality
* 🖥️ GUI interface
* 🌐 Multi-user environment

---

## 👨‍💻 Author

**Lovenish **
IIT Hyderabad
Aspiring Software Engineer | Interested in Systems & Backend Development

---

