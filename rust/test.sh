printf "Test: normal cargo run\n"
cargo run
sleep 1s

printf "\nTest: cargo run with invalid path\n"
cargo run this_file_dont_exist.bf
sleep 1s

printf "\nTest: cargo run with valid path and valid code\n"
cargo run ../brainfuck/neo.bf
