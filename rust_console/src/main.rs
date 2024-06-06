use std::fmt::Display;
use std::io::{stdin, stdout, Write};

#[derive(Clone, PartialEq)]
enum State {
    X,
    O,
    Empty,
    Obstructed,
}

struct Input {
    x: usize,
    y: usize,
}

#[derive(Clone)]
struct Cell {
    state: State,
    age: u8,
}

struct Board {
    grid: Vec<Vec<Cell>>,
    width: usize,
    height: usize,
    // Team state
}

static DEBUG: bool = false;

impl Board {
    pub fn new(width: usize, height: usize) -> Self {
        return Board {
            grid: vec![
                vec![
                    Cell {
                        state: State::Empty,
                        age: 0
                    };
                    width
                ];
                height
            ],
            width,
            height,
        };
    }

    pub fn place(&mut self, x: usize, y: usize, state: State) {
        // Check for trying to Set O space as X
        // In general wrong sets
        // Check in bounds

        if self.grid[x][y].state != State::Empty {
            //ERROR
        }

        self.grid[x][y].state = state;
        self.grid[x][y].age = 0;
    }

    pub fn tick(&mut self) {
        for col in &mut self.grid {
            for cell in col {
                match cell.state {
                    State::X | State::O => {
                        if cell.age >= 5 {
                            cell.state = State::Obstructed;
                            continue;
                        }

                        cell.age += 1;
                    }
                    State::Obstructed => {
                        cell.state = State::Empty;
                        cell.age = 0;
                    }
                    // Ignore Empty State
                    _ => {}
                }
            }
        }
    }
}

impl Display for Board {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        // Goal:
        // x |   |
        //---+---+---
        //   |   |
        //---+---+---
        //   |   |

        // Maybe jut use  mut String and write all at once?

        if DEBUG {
            for y in 0..self.height {
                for x in 0..self.width {
                    if x >= 1 {
                        write!(f, "|")?;
                    }

                    write!(f, " {} ", self.grid[x][y].age)?;                    
                }

                writeln!(f, "")?;

                if y >= self.height - 1 {
                    continue;
                }

                for i in 0..self.height {
                    if i >= 1 {
                        write!(f, "+")?;
                    }

                    write!(f, "---")?;
                }

                writeln!(f, "")?;
            }

            writeln!(f, "")?;
        }

        for y in 0..self.height {
            for x in 0..self.width {
                if x >= 1 {
                    write!(f, "|")?;
                }

                match self.grid[x][y].state {
                    State::X => {
                        write!(f, " X ")?;
                    }
                    State::O => {
                        write!(f, " O ")?;
                    }
                    State::Obstructed => {
                        write!(f, " = ")?;
                    }
                    State::Empty => {
                        write!(f, "   ")?;
                    }
                }
            }

            writeln!(f, "")?;

            if y >= self.height - 1 {
                continue;
            }

            for i in 0..self.height {
                if i >= 1 {
                    write!(f, "+")?;
                }

                write!(f, "---")?;
            }

            writeln!(f, "")?;
        }

        return Ok(());
    }
}

fn main() {
    let mut board: Board = Board::new(3, 3);

    // Create Game loop

    let mut turn_number: u8 = 0;

    loop {
        board.tick();

        println!("{}", board);

        if turn_number % 2 == 0 {
            println!("Current Turn: X");
        } else {
            println!("Current Turn: O");
        }

        let input_raw: String = get_input_raw();
        let input: Input = parse_input(input_raw);

        board.place(
            input.x,
            input.y,
            if turn_number % 2 == 0 {
                State::X
            } else {
                State::O
            },
        );

        turn_number += 1;
    }
}

fn get_input_raw() -> String {
    let mut input_raw = String::new();

    print!("Gathering Input (x y): ");

    stdout().flush().unwrap();

    stdin().read_line(&mut input_raw).expect("Unexpected Input");

    return input_raw;
}

// This should be able to error
fn parse_input(input_raw: String) -> Input {
    let values: Vec<&str> = input_raw.split(' ').collect();

    // Check to make sure length is only 1

    let x = values[0].trim().parse::<usize>().unwrap();
    let y = values[1].trim().parse::<usize>().unwrap();

    return Input { x, y };
}
