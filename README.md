# 🐍 Snake Game (Qt & C++)

This is a classic Snake game implemented using **Qt (via QML or Widgets)** and **C++**, designed to be extensible and fun to play. It includes modern gameplay features such as border placement toggling, self-crossing, and no-death mode.

---

## 🎮 Controls

| Key         | Action                        |
| ----------- | ----------------------------- |
| **↑ ↓ ← →** | Change snake direction        |
| **Q**       | Quit the game                 |
| **P**       | Pause / unpause               |
| **R**       | Reset game state              |
| **S**       | Start the game                |
| **F**       | Toggle game speed (slow/fast) |
| **B**       | Toggle no border collision    |
| **D**       | Toggle no border placement    |
| **N**       | Toggle no-death mode          |

> ✅ Movement is allowed only if not reversing direction.

---

## 🧪 Game Modes

- **Border Mode**: Hit the border and the snake dies — or not! Toggle with **B**.
- **Crossing Mode**: Food wont be placed directly on the border (**D**).
- **No-Death Mode**: Makes the snake immortal to collisions (**N**).
