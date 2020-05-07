# Bughouse Chess
Read [this document](https://cliutils.gitlab.io/modern-cmake/chapters/basics/structure.html) to understand the project
layout.
[![license](https://img.shields.io/badge/license-MIT-green)](LICENSE)
[![docs](https://img.shields.io/badge/docs-yes-brightgreen)](docs/README.md)

Bughouse chess is a 2 – 4 player blitz chess match (5 minutes per person, no time delay, 2 teams, 2 boards). 
In a real match, it is a best out of 3 tournament. This is a stretch goal.
### Quick rules: 
1. The person who runs of time or gets their king captured first loses the game, and their team lose.
1. Every time you capture an opponent’s piece, you immediately give that piece to your partner. They 
can then place that piece anywhere on their own board (with some restrictions for pawns and queened pawns).
1. In this fast paced game, being under check is no longer a restriction 
(if you choose to not move out of check or do not notice it, the opponent will just capture your king, and you lose). 
1. Once either player in the team loses against his opponent, the game is over.
1. Otherwise, most standard blitz chess rules apply.

### Stretch goals
The idea is that the game would be played on four screens, one per person, and each screen would be a 
board with the person and their opponent’s board. However, I do not think it is feasible for me to implement this; 
I have zero experience with TCP/UDP networks. I hope to implement this in the future. Without the networking,
 it will look like 2 boards on the screen (one for each team, the computer is passed around). 

Abstract factoring - book "design patterns"
 
 ### Motive
 My motivation for this assignment is that I love chess, and I was originally just going to 
 implement a chess app, but after minimal research I already found previous people that have done this. 
 I then remembered that I have always wanted to be able to play bughouse chess online 
 (because I usually don’t have 3 other chess-playing friends and 2 boards available to play in the moment), 
 and I remember scouring the App Store in high school for a bughouse chess game and failing.
  Back then, I gave up at that, but now, the thought of implementing one myself is very exciting. 
 
 
### Timeline:
* Week 1 - Start Graphics, organize game into classes/files.
* Week 2 - Fill out logic, continue graphics the graphics
* Week 3 - Debug / Test / finish up anything remaining

### Extra links
Gif library:
https://github.com/cwhitney/ciAnimatedGif

**Author**: Tomoko Sakurayama - [`tomokos2@illinois.edu`](mailto:tomokos2@illinois.edu)

