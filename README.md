# Antichess (Giveaway Chess)

A chess variant where the goal is to **lose all your pieces** or **have no legal moves**.  
Built with **Qt 6** and **C++17**.

---

## Rules (Giveaway / Antichess)

- The player who **has no pieces left** or **cannot make a move** wins.
- **Captures are compulsory** – if you can capture, you must take a piece (and if multiple captures are possible, you may choose any).
- The king is a normal piece; it can be captured like any other.
- **Pawns can promote to any piece (including a king)** when they reach the last rank.

---

## Features

- **Local multiplayer** – two players on the same PC.
- **Play against a bot** – three difficulty levels:
  - **Bot 0** – random legal moves.
  - **Bot 1** – minimax search (fixed depth, no alpha-beta).
  - **Bot 2** – minimax with alpha-beta pruning (deeper search).
- **Bot vs Bot mode** – watch two bots play against each other.
- **Choose your colour** when playing against a bot.
- **Pawn promotion dialog** – player selects a piece; bots choose randomly (or optimally in Bot 1/2).
- **Escape key** returns to the main menu.
