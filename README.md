# cellular-automata
A demonstration of Belousov Zhabotinsky's cellular automata


## Rules
- A cell may be in three states: on, dying, off
- Each cell has eight neighbors(Moore)
- A cell turns on if it was off but has *exactly* 2 neighbors that are on
- All cells that are on go into the dying state
- All cells in the dying state turn off