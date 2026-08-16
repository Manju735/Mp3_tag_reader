<div align="center">

# 🎧 MP3 Tag Reader

### *Peek inside your MP3s. Read the story hidden in their bytes.*

[![Language](https://img.shields.io/badge/Language-C-00599C?style=for-the-badge&logo=c&logoColor=white)](https://en.wikipedia.org/wiki/C_(programming_language))
[![Platform](https://img.shields.io/badge/Platform-Linux-FCC624?style=for-the-badge&logo=linux&logoColor=black)](https://www.linux.org/)
[![Build](https://img.shields.io/badge/Build-GCC-A42E2B?style=for-the-badge&logo=gnu&logoColor=white)](https://gcc.gnu.org/)
[![Status](https://img.shields.io/badge/Status-Active-brightgreen?style=for-the-badge)](#)
[![License](https://img.shields.io/badge/License-MIT-blue?style=for-the-badge)](#-license)

*A lightweight, no-dependency, pure-C tool that reads and edits the ID3v1 metadata tucked into every MP3 file — no libraries, just raw bytes and a bit of pointer wizardry.*

</div>

---

## 🌟 Why This Exists

Every MP3 file secretly carries a small passport at its tail end — 128 bytes that hold its **title, artist, album, year, comment, and genre**. This project decodes that passport by hand, byte by byte, with zero external libraries — just `stdio.h`, `string.h`, and disciplined pointer arithmetic.

> Think of it as X-ray vision for your music library. 🩻🎶

---

## ✨ Features

| | Feature | Description |
|---|---|---|
| 👁️ | **View Mode** | Instantly print Title, Artist, Album, Year, Comment & Genre from any MP3 |
| ✏️ | **Edit Mode** | Rewrite any tag field in-place — no re-encoding, no quality loss |
| ⚙️ | **Byte-Level Parsing** | Manually walks the ID3v1 128-byte trailer with correct offsets |
| 🪶 | **Zero Dependencies** | Pure C, standard library only — compiles anywhere GCC runs |
| 🧪 | **Sample Included** | Ships with `sample.mp3` so you can try it out immediately |

---

## 🗂️ Project Anatomy

```
Mp3_tag_reader/
├── mp3_main.c        🚪  Entry point — parses args, routes to view/edit
├── mp3_view.c         👁️  Extracts & displays ID3v1 tag data
├── mp3_edit.c         ✏️  Rewrites tag fields safely
├── functions.c        ⚙️  Validation, endianness & printing helpers
├── mp3_header.h        🧩  Struct definitions & shared prototypes
└── sample.mp3          🎵  Test file to try things out on
```

---

## 🧬 How It Works — Under the Hood

```
┌──────────────────────────────────────────────┐
│                MP3 AUDIO DATA                 │
│                (untouched)                    │
├──────────────────────────────────────────────┤
│  "TAG"  │ Title │ Artist │ Album │ Year │ ... │  ← last 128 bytes
└──────────────────────────────────────────────┘
   3B        30B      30B     30B    4B
```

The ID3v1 spec packs metadata into the **final 128 bytes** of the file. This tool:

1. Opens the MP3 in **binary mode**
2. `fseek`s straight to `EOF - 128`
3. Reads the block into a `struct MP3`
4. **View mode** → prints each field cleanly to the terminal
5. **Edit mode** → overwrites only the requested field, byte-for-byte, leaving the audio stream completely intact

No decoding of audio frames. No corruption risk. Surgical precision. 🔬

---

## 🚀 Quick Start

### 1️⃣ Clone it

```bash
git clone https://github.com/Manju735/Mp3_tag_reader.git
cd Mp3_tag_reader
```

### 2️⃣ Build it

```bash
gcc mp3_main.c mp3_view.c mp3_edit.c functions.c -o mp3_tag_reader
```

### 3️⃣ Run it

```bash
# View tags
./mp3_tag_reader -v sample.mp3

# Edit tags
./mp3_tag_reader -e sample.mp3
```

> 💡 Exact flags/prompts are defined in `mp3_main.c` / `functions.c` — check `validate_cla()` if your build uses different arguments.

---

## 📸 Sample Output

```
──────────────────────────────
   🎵  MP3 TAG DETAILS  🎵
──────────────────────────────
 Title    : Midnight Drive
 Artist   : The Wanderers
 Album    : Neon Nights
 Year     : 2025
 Comment  : Made with mp3_tag_reader
 Genre    : Electronic
──────────────────────────────
```

---

## 🛠️ Tech Stack

<div align="center">

![C](https://img.shields.io/badge/-C-05122A?style=flat-square&logo=c)
![GCC](https://img.shields.io/badge/-GCC-05122A?style=flat-square&logo=gnu)
![Linux](https://img.shields.io/badge/-Linux-05122A?style=flat-square&logo=linux)
![Binary I/O](https://img.shields.io/badge/-Binary%20File%20I%2FO-05122A?style=flat-square)

</div>

---

## 🧗 Challenges Faced

Building the **edit** function was the hardest part:

- 🎯 Precisely locating each tag field's offset
- 🧱 Handling fixed vs. variable-size fields without shifting data
- 🔄 Managing byte alignment & endianness carefully
- 🧵 Overwriting only the intended bytes — leaving audio data untouched

Solved through careful offset math, defensive validation, and a lot of `xxd` debugging. 🐛→✅

---

## 🗺️ Roadmap

- [ ] Add ID3v2 tag support
- [ ] Command-line flag for batch processing multiple files
- [ ] Optional GUI wrapper
- [ ] Unit tests for edge cases (empty tags, corrupted headers)

---

## 👤 Author

**H Manjunatha**
📅 Built: May 2026

<div align="center">

[![GitHub](https://img.shields.io/badge/GitHub-Manju735-181717?style=for-the-badge&logo=github)](https://github.com/Manju735)

</div>

---

## 📄 License

Licensed under the **MIT License** — free to use, modify, and distribute.

---

<div align="center">

### ⭐ If this helped you understand ID3 tags, drop a star!

*Made with C, curiosity, and a healthy respect for byte offsets.*

</div>
