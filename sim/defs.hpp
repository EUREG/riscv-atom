/**
 * @brief Version information
 */
const char Info_version[] = "AtomSim v1.0";

/**
 * @brief Copyright message
 */
const char Info_copyright[] = 
"MIT License\n\n"

"Copyright (c) 2020 EUREG\n\n"

"Permission is hereby granted, free of charge, to any person obtaining a copy\n"
"of this software and associated documentation files (the \"Software\"), to deal\n"
"in the Software without restriction, including without limitation the rights\n"
"to use, copy, modify, merge, publish, distribute, sublicense, and/or sell\n"
"copies of the Software, and to permit persons to whom the Software is\n"
"furnished to do so, subject to the following conditions:\n\n"

"The above copyright notice and this permission notice shall be included in all\n"
"copies or substantial portions of the Software.\n\n"

"THE SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR\n"
"IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,\n"
"FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE\n"
"AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER\n"
"LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,\n"
"OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE\n"
"SOFTWARE.\n";

// ================== Color codes for output formatting ====================
const std::string  COLOR_RESET  = "\033[0m";
const std::string  COLOR_RED    =  "\033[31m";      
const std::string  COLOR_GREEN  =  "\033[32m";      
const std::string  COLOR_YELLOW =  "\033[33m";


// ================================ THROWING ERRORS =======================================
/**
 * @brief Exits the program
 */
void Exit()
{
    std::exit(EXIT_FAILURE);
}


/**
 * @brief Throws error generated in the std::cerr stream
 * 
 * @param er_code error code 
 * @param message error message
 * @param exit flag that tells weather to exit immidiately
 */
void throwError(std::string er_code, std::string message, bool exit = false)
{
    std::cerr << COLOR_RED <<"! ERROR  (E"<< er_code <<"): " << COLOR_RESET << message << std::endl;
    if(exit)
    {
        Exit();
    }
}


/**
 * @brief Throws warning generated by assembler in the std::cerr stream
 * 
 * @param wr_code warning code 
 * @param message Warning message
 */
void throwWarning(std::string wr_code, std::string message)
{
    std::cerr << COLOR_YELLOW <<"! WARNING (W"<< wr_code <<"): " << COLOR_RESET << message << std::endl;
}


/**
 * @brief Displays a success messaage
 * 
 * @param message Success message
 */
void throwSuccessMessage(std::string message)
{
    std::cout << COLOR_GREEN <<"SUCCESS : " << COLOR_RESET  << message <<std::endl;
}


/**
 * @brief String stripping utility functions
 * 
 * @see https://www.techiedelight.com/trim-string-cpp-remove-leading-trailing-spaces/#:~:text=We%20can%20use%20combination%20of,functions%20to%20trim%20the%20string.
 */
const std::string WHITESPACE = " \n\r\t\f\v";


/**
 * @brief removes preceeding whitespaces in a string
 * 
 * @param s string
 * @return std::string 
 */
std::string lStrip(const std::string& s)
{
    size_t start = s.find_first_not_of(WHITESPACE);
    return (start == std::string::npos) ? "" : s.substr(start);
}


/**
 * @brief removes succeding whitespaces in a string
 * 
 * @param s string
 * @return std::string 
 */
std::string rStrip(const std::string& s)
{
    size_t end = s.find_last_not_of(WHITESPACE);
    return (end == std::string::npos) ? "" : s.substr(0, end + 1);
}


/**
 * @brief removes preceding & succeding whitespaces in a string
 * 
 * @param s string
 * @return std::string 
 */
std::string strip(const std::string& s)
{
    return rStrip(lStrip(s));
}


// =============================== STRING TOKENIZING =====================================
/**
 * @brief splits a string accordint to delimiter 
 * 
 * @param txt input string
 * @param strs vector of strings parts
 * @param ch delimiter
 * @return size_t 
 */
size_t tokenize(const std::string &txt, std::vector<std::string> &strs, char ch)
{
    size_t pos = txt.find( ch );
    size_t initialPos = 0;
    strs.clear();

    // Decompose statement
    while( pos != std::string::npos ) {
        strs.push_back( txt.substr( initialPos, pos - initialPos ) );
        initialPos = pos + 1;

        pos = txt.find( ch, initialPos );
    }

    // Add the last one
    strs.push_back( txt.substr( initialPos, std::min( pos, txt.size() ) - initialPos + 1 ) );

    return strs.size();
}


/**
 * @brief reads a binary file
 * 
 * @param memfile filepath
 * @return std::vector<char> contents
 */
std::vector<char> fReadBin(std::string memfile)
{        
    std::vector<char> fcontents;
    std::ifstream f (memfile, std::ios::out | std::ios::binary);
    
    if(!f)
    {
        throw "file access failed";
    }
    try
    {
        while(!f.eof())
        {    
            char byte;
            f.read((char *) &byte, 1);
            fcontents.push_back(byte);
        }
    }
    catch(...)
    {
        throw "file reading failed!";
    }
    f.close();
    return fcontents;
}


/**
 * @brief Reads a file and returns its contents
 * 
 * @param filepath Filepath
 * @return Vector of strings containing file contents
 */
std::vector<std::string> fRead (std::string filepath)
{
    // returns a vector of strings
    std::vector<std::string> text;

    // input file stream
    std::ifstream fin(filepath.c_str());
    if(!fin){
        throw "file access failed";
    }

    // reading file line by line and appending into the vector of strings
    std::string raw_line;
    while(getline(fin,raw_line))
    {
        text.push_back(raw_line);
    }

    // close file
    fin.close();
    return text;
}


// =================================== FILE WRITER ====================================
/**
 * @brief Write to a file
 * 
 * @param filepath Filepath
 */
void fWrite (std::vector<std::string> data, std::string filepath)
{
    std::ofstream File(filepath);
    if(!File)
    {
        throw "file writing failed";
    }
    for(unsigned int i=0; i<data.size(); i++)
    {
        File << data[i] <<"\n";
    }
    File.close();
}

// ================================ Runtime disassembly =================================
/**
 * @brief Get the Stdout From shell Command
 * 
 * @param cmd shell command to execute
 * @return std::string command output
 */
std::string GetStdoutFromCommand(std::string cmd) {

  std::string data;
  FILE * stream;
  const int max_buffer = 256;
  char buffer[max_buffer];
  cmd.append(" 2>&1");

  stream = popen(cmd.c_str(), "r");

  if (stream) {
    while (!feof(stream))
      if (fgets(buffer, max_buffer, stream) != NULL) data.append(buffer);
    pclose(stream);
  }
  return data;
}

/**
 * @brief Get the Disassembly of input file using riscv objdump
 * 
 * @param filename input filename
 * @return std::map<uint32_t, std::string> map of disassembly
 */
std::map<uint32_t, std::string> getDisassembly(std::string filename)
{
	std::string command = "";
	#ifdef RV32_COMPILER
		command +="riscv32-unknown-elf-objdump -d ";
	#else
		command += "riscv64-unknown-elf-objdump -d ";
	#endif
	command+=filename;
	
	// Get command output
	std::string output = GetStdoutFromCommand(command);
	
	std::stringstream s(output);

	// Parse command output
	std::map<uint32_t, std::string> dis;
	
	std::string line;
	while(std::getline(s, line))
	{
		for(unsigned int i=0; i<line.length(); i++)
		{
			if(line[0]==' ' && line[i]==':')
			{
				uint32_t adr = std::stoi(strip(line.substr(0, i)).c_str(), 0, 16);
				std::string op = strip(line.substr(i+21, line.length()));
				dis.insert({adr, op});
				break;
			}
		}
	}
	return dis;
}