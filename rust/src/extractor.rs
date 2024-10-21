use std::fs;

/* Extracts the code from the source code
 */
pub fn get_code_from_file(file_path: &String) -> Result<Vec<char>, ()> {
    match fs::read_to_string(file_path) {
        Err(_) => Err(()),
        Ok(content) => Ok(content.chars().collect())
    }
}
