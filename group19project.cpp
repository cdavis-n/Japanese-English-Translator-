#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;

/* Look for all **'s and complete them */

//=====================================================
// File scanner.cpp written by: Group Number: 19 
//=====================================================

// --------- Two DFAs ---------------------------------

// WORD DFA 
// Done by: Chihiro Nishijima
// RE:  ( vowel | vowel n | consonant vowel | consonant vowel n | consonant-pair vowel | consonant-pair vowel n)^+ 
bool word (string s)
{
  int state = 0;    // declare integer called state as 0 for state number; DFA diagram: 0='q0', 1='q0q1', 2='q0qy', 3='qc', 4='qt', 5='qsa', 6='qy', 7='qs' 
  int charpos = 0;  // declare integer called charpos as 0 for each position in the string s.
  vector<char> vowel = {'a', 'i', 'I', 'u', 'e', 'E', 'o'};
  vector<char> bmknhprg = {'b', 'm', 'k', 'n', 'h', 'p', 'r', 'g'};
  vector<char> dwzyj = {'d', 'w', 'z', 'y', 'j'};
  
  //replace the following todo the word dfa  **
  while (s[charpos] != '\0')  // check every character in the position of string s. 
    {
      if ((state >= 0 && state <= 7) && find(vowel.begin(), vowel.end(), s[charpos]) != vowel.end()) // if current state: 0, 1, 2, 3, 4, 5, 6, or 7; the character at charpos is any character in vowel vector(:'a', 'i', 'I', 'u', 'e', 'E', 'o')
      state = 1; // then go to state 1.
      else
      if (state == 1 && s[charpos] == 'n')  // current state: 1; if the character at charpos is 'n'
      state = 2;  // then go to state 2.
      else
      if ((state >= 0 && state <= 2) && s[charpos] == 'c') // if current state: 0, 1, or 2; the character at charpos is 'c'
      state = 3;  // then go to state 3.
      else
      if ((state >= 0 && state <= 2) && s[charpos] == 't') // if current state: 0, 1, or 2;  the character at charpos is 't'
      state = 4;  // then go to state 4.
      else                                        // either of these cases below...
      if ((state == 3 && s[charpos] == 'h') ||    // if current state: 3;  the character at charpos is 'h' 
          (state == 7 && s[charpos] == 'h') ||    // if current state: 7;  the character at charpos is 'h' 
          (state == 4 && s[charpos] == 's') ||    // if current state: 4;  the character at charpos is 's' 
          (state == 6 && s[charpos] == 'y') ||    // if current state: 6;  the character at charpos is 'y' 
          ((state >= 0 && state <= 2) && find(dwzyj.begin(), dwzyj.end(), s[charpos]) != dwzyj.end()))   // if current state: 0, 1, or 2;  the character at charpos is any character in dwzyj vector(:'d', 'w', 'z', 'y', 'j')
      state = 5;  // then go to state 5.
      else
      if ((state >= 0 && state <= 2) && find(bmknhprg.begin(), bmknhprg.end(), s[charpos]) != bmknhprg.end())   // if current state: 0, 1, or 2;  the character at charpos is any character in bmknhprg vector(:'b', 'm', 'k', 'n', 'h', 'p', 'r', 'g')
      state = 6;  // then go to state 6.
      else
      if ((state >= 0 && state <= 2) && s[charpos] == 's') // if current state: 0, 1, or 2; the character at charpos is 's'
      state = 7;  // then go to state 7.
      else
	    return(false); // otherwise, return false which means this string is not suitable for this token. 
      charpos++;  // add 1 into charpos to move to the next character.
    }//end of while

  // where did I end up????
  if (state == 0 || state == 1 || state == 2) return(true);  // end in a final state: if state ends up either 0, 1 or 2, then return true. 
   else return(false);  // otherwise return false.
}

// PERIOD DFA 
// Done by: Chihiro Nishijima
// RE: .
bool period (string s)
{  
   int state = 0;     // declare integer called state as 0 for state number.
   if(state == 0 && s == ".") // if current state: 0; the string is "."
   {
      state = 1;  // then go to state 1.
      return (true); // since state ends up 1, return true meaning the string is suitable for this token.
   } else return(false); // otherwise, return false.
}

// ------ Three  Tables -------------------------------------

// TABLES Done by: Chihiro Nishijima

// ** Update the tokentype to be WORD1, WORD2, PERIOD, ERROR, EOFM, etc.
enum tokentype {ERROR, WORD1, WORD2, PERIOD, VERB, VERBNEG, VERBPAST, VERBPASTNEG, IS, WAS, 
                OBJECT, SUBJECT, DESTINATION, PRONOUN, CONNECTOR, EOFM};

// ** For the display names of tokens - must be in the same order as the tokentype.
string tokenName[30] = {"ERROR", "WORD1", "WORD2", "PERIOD", "VERB", "VERBNEG", "VERBPAST", "VERBPASTNEG", "IS", "WAS", 
                "OBJECT", "SUBJECT", "DESTINATION", "PRONOUN", "CONNECTOR", "EOFM"}; 

// ** Need the reservedwords table to be set up here. 
// ** Do not require any file input for this. Hard code the table.
// ** a.out should work without any additional files.
// structure w_words with string wd and enum's tokentype t to check reserved words in scanner() function.
struct r_words 
{
   string wd;
   tokentype t;
};
r_words reservedWordsTable[] = {{"masu", VERB}, 
                                       {"masen", VERBNEG},
                                       {"mashita", VERBPAST},
                                       {"masendeshita", VERBPASTNEG},
                                       {"desu", IS},
                                       {"deshita", WAS},
                                       {"o", OBJECT},
                                       {"wa", SUBJECT},
                                       {"ni", DESTINATION},
                                       {"watashi", PRONOUN},
                                       {"anata", PRONOUN},
                                       {"kare", PRONOUN},
                                       {"kanojo", PRONOUN},
                                       {"sore", PRONOUN},
                                       {"mata", CONNECTOR},
                                       {"soshite", CONNECTOR},
                                       {"shikashi", CONNECTOR},
                                       {"dakara", CONNECTOR},
                                       {"eofm", EOFM}};

// ------------ Scanner and Driver ----------------------- 

ifstream fin;  // global stream for reading from the input file

// Scanner processes only one word each time it is called
// Gives back the token type and the word itself
// ** Done by: Chihiro Nishijima
int scanner(tokentype& tt, string& w)
{ 
  fin >> w;   // ** Grab the next word from the file via fin
  cout << "Scanner called using word: " << w << endl;      // print out the word checked in scanner.
  
  if(w == "eofm") // if the word is eofm, 
  { tt = EOFM; return 0;}    // return right now.
  
  if(period(w))       // if period(w) is true meaning w is a valid token of PERIOD,
  { tt = PERIOD; }    // set tokentype tt as PERIOD. 
  else 
  if(word(w))         // else if word(w) is true meaning w is a valid token of WORD,
  {
     int endpos = w.length() - 1;  // declare integer charpos as the string w's size - 1 to get the last character of w.
     bool flag = false;    // declare flag as false to check whether or not the word is reserved. false = NOT reserved; true = reserved.
     int size = sizeof(reservedWordsTable)/sizeof(reservedWordsTable[0]);  // declare the size of reservedWordsTable.
     for(int i = 0; i < size; i++)  // check the every words in the table. 
     {
         if (reservedWordsTable[i].wd == w)  // if the word is found in the reservedWordsTable
         {
            tt = reservedWordsTable[i].t;
            flag = true;     // set the flag is true which means the word is reserved.
            break;
         }  // end of if
     }  // end of for
     if (flag)   // if flag is true meaning the word is reserved,
     {  tt = tt;  }    // the tokentype is the type set as reservedWordsTable[i].t.
     else
     if (w[endpos] == 'I' || w[endpos] == 'E')  // if the last character of string w is either 'I' or 'E',
     {  tt = WORD2; }                           // set tokentype as WORD2.
     else
     {  tt = WORD1; }                          // otherwise, set tokentype as WORD1.
  } // end of if
  else
  {
     cout << endl << "Lexical Error: " << w << " is not a valid token" << endl;  // print out the Lexical error message with the word.
     tt = ERROR;                                                            // set the tokentype as ERROR.
  } // end of else
  return 0;   // retun the tokentype and the string (pass by reference)

}//the end of scanner

//============================= parser.cpp ============================================

/* INSTRUCTION:  Complete all ** parts.
   You may use any method to connect this file to scanner.cpp
   that you had written.  
  e.g. You can copy scanner.cpp here by:
          cp ../ScannerFiles/scanner.cpp .  
       and then append the two files into one: 
          cat scanner.cpp parser.cpp > myparser.cpp
*/

//=================================================
// File parser.cpp written by Group Number: 19
//=================================================

// ----- Four Utility Functions and Globals -----------------------------------

// ** Need syntaxerror1 and syntaxerror2 functions (each takes 2 args)
//    to display syntax error messages as specified by me.
// ** Need the updated match and next_token with 2 global vars
// saved_token and saved_lexeme

tokentype saved_token;
string saved_lexeme;

ofstream errorfile;

bool token_available;
bool t_flag; // trasing messege flag: true = turn on & false = turn off

// Purpose: Finds the value of the next token, which can then be passed to the "match" function. 
// Done by: Ryan Michels
tokentype next_token() // pass back token type into global variable
{
  if(!token_available) //fetch next token if there isnt already one available to analyze
    {
      scanner(saved_token, saved_lexeme);
      token_available = true;
    }
  return saved_token;
}

// Type of error: Match fails
// Done by: Ricardo Lizarraga, Chihiro Nishijima(syntax error recovery)
bool syntaxerror1(tokentype token_type, string saved_lexeme){
    cout << "SYNTAX ERROR: expected " << tokenName[token_type] << " but found " << saved_lexeme << endl;
    string input;
    cout << "Skip or replace the token? (s/r): ";
    cin >> input;
    
    if(input == "s") // if the user choice is "skip"
    {
       errorfile << "SYNTAX ERROR: expected " << tokenName[token_type] 
                 << " but found " << saved_lexeme << endl; // error message for errors.txt
       token_available = false; // false to go to the next token in scanner.
       if(next_token() != token_type)  // if the token is incorrect then syntaxerror1 again.
         syntaxerror1(token_type, saved_lexeme);
       else
      {
        token_available = false; // false to go to the next token in scanner
        if(t_flag == true)  // if tracing feature is turned on by the user
           cout << "Matched " << tokenName[saved_token] << endl;
        return true;  // get out from this function.
      } // end of else
    } // end of if
    else 
    if(input == "r") // if the user choice is "replace"
    {
       errorfile << "SYNTAX ERROR: expected " << tokenName[token_type] 
                 << " but found " << saved_lexeme << endl;  // error message for errors.txt
       saved_token = token_type; 
       token_available = false;
       if(t_flag == true)
         cout << "Matched " << tokenName[token_type] << endl;
       return true;
    } // end of else if
}

// Type of error: Switch default in a parser function
// Done by: Ricardo Lizarraga
void syntaxerror2(string saved_lexeme, string parser_function) {
    cout << "SYNTAX ERROR: unexpected " << saved_lexeme << " found in " << parser_function << endl;
    exit(1);
}


// Purpose: Checks the next token to see if it follows the RDP rules. RDP = "Recursive Descent Parsing"
// Done by: Ryan Michels
bool match(tokentype expected) 
{
  if(next_token() != expected) // if returned token value doesnt == expected, error. Else a match
    {
      syntaxerror1(expected, saved_lexeme);
    }
  else
    {
      token_available = false; //ready up the next_token
      if(t_flag == true)
         cout << "Matched " << tokenName[saved_token] << endl;
      return true; // there was a match!!!
    }
}


string filename;
ofstream outfile;
//============================ translator.cpp =====================================================

/* INSTRUCTION:  copy your parser.cpp here
      cp ../ParserFiles/parser.cpp .
   Then, insert or append its contents into this file and edit.
   Complete all ** parts.
*/

//=================================================
// File translator.cpp written by Group Number: 19
//=================================================

// ----- Additions to the parser.cpp ---------------------

// ** Declare Lexicon (i.e. dictionary) that will hold the content of lexicon.txt
// Make sure it is easy and fast to look up the translation.
// Do not change the format or content of lexicon.txt 
//  Done by: Chihiro Nishijima
vector<vector<string>> dictionary;

// ** Additions to parser.cpp here:
string saved_E_word;
// #getEword# function
//  Obtain English word from dictionary
//  Done by: Ricardo Lizarraga

void getEword() {
    for (int i = 0; i < dictionary.size(); i++) {    //For loop to run through dictionary
        vector<string> entry = dictionary[i];        //Entry from dictionary
        if(saved_lexeme.compare(entry[0]) == 0)        //Compare saved_lexeme with Japanese entry
          {  
            saved_E_word = entry[1];                //If the same, place the English entry into saved_E_word
            return;                                 //Leave function
          }                             
    }
    saved_E_word = saved_lexeme;  
}                 
//  Done by: Ryan Michels
//  Generates the semantic lines, given an input string 

void gen(string str) 
{
    if(str == "TENSE")
    {
        outfile <<str<<": "<<tokenName[saved_token]<<endl; //Print out the tense
    }
    else
    {
        outfile <<str<<": "<<saved_E_word<<endl; //Print out the english word
    }
}

// ----- Changes to the parser.cpp content ---------------------

// ** Comment update: Be sure to put the corresponding grammar 
//    rule with semantic routine calls
//    above each non-terminal function 

// ** Each non-terminal function should be calling
//    getEword and/or gen now.

// Grammar: <tense>::=VERBPAST | VERBPASTNEG | VERB | VERBNEG
// Done by: Chihiro Nishijima
void tense()
{
   if(t_flag == true)
      cout << "Processing <tense>" << endl;   // print out the message mentioning the beginning of tense parser function.
   switch(next_token())           // check next_token()
   {
      case VERBPAST:              // if next_token() is VERBPAST
         match(VERBPAST);         // match VERBPAST
         break;                   // then break to get out of switch
      case VERBPASTNEG:           // if next_token() is VERBPASTNEG
         match(VERBPASTNEG);      // match VERBPASTNEG
         break;                   // then break to get out of switch
      case VERB:                  // if next_token() is VERB
         match(VERB);             // match VERB
         break;                   // then break to get out of switch
      case VERBNEG:               // if next_token() is VERBNEG
         match(VERBNEG);          // match VERBNEG
         break;                   // then break to get out of switch
      default:                    // otherwise,
         syntaxerror2(saved_lexeme, "tense"); // go to syntaxerror2 to mention the error
   }
}
// Grammar: <be>::=IS | WAS
// Done by: Richard Fina
void be()
{
    if(t_flag == true)
       cout << "Processing <be>" << endl;
    switch(next_token())
    {
        case IS:
            match(IS);
            break;
        case WAS:
            match(WAS);
            break;
        default:
            syntaxerror2(saved_lexeme,"be");
    }
}
// Grammar: <verb>::=WORD2
// Done by: Richard Fina
void verb()
{
    if(t_flag == true)
       cout << "Processing <verb>" << endl;
    switch(next_token())
    {
        case WORD2:
            match(WORD2);
            break;
        default:
            syntaxerror2(saved_lexeme, "verb");
    }
}
// Grammar: <noun>::=WORD1 | PRONOUN
// Done by: Richard Fina
void noun()
{
    if(t_flag == true)
       cout << "Processing <noun>" << endl;
    switch(next_token())
    {
        case WORD1:
            match(WORD1);
            break;
        case PRONOUN:
            match(PRONOUN);
            break;
        default:
            syntaxerror2(saved_lexeme, "noun");
    }
}
// Grammar: <afterObject>::=<verb> #getEword# #gen(“ACTION”)# <tense> #gen(“TENSE”)# PERIOD | 
//                          <noun> #getEword# DESTINATION #gen(“TO”)# <verb> #getEword# #gen(“ACTION”)# <tense> #gen(“TENSE”)# PERIOD
// Done by: Ryan Michels
void afterObject()
{
    if(t_flag == true)
        cout << "Processing <afterObject>" << endl;
    switch(next_token())
    {
        case WORD2:               // WORD2 == verb
          verb();
          getEword();            //Grab english word (if available)
          gen("ACTION");        //Generate "ACTION"
          tense();
          gen("TENSE");            //Generate "TENSE"
          match(PERIOD);
          outfile << endl;
          break;
       case WORD1:               // WORD1/PRONOUN == noun
       case PRONOUN:
          noun();
          getEword();            //Grab english word
          match(DESTINATION);
          gen("TO");            //Generate "ACTION"
          verb();
          getEword();            //Grab english word
          gen("ACTION");
          tense();
          gen("TENSE");            //Generate "TENSE"
          match(PERIOD);
          outfile << endl;
          break;
       default: 
          syntaxerror2(saved_lexeme, "afterObject"); 
    }
}
// Grammar: <afterNoun>::=<be> #gen(“DESCRIPTION”)# #gen(“TENSE”)# PERIOD | 
//                        DESTINATION #gen(“TO”)# <verb> #getEword# #gen(“ACTION”)# <tense> #gen(“TENSE”)# PERIOD | 
//                        OBJECT #gen(“OBJECT”)# <afterObject>
// Done by: Richard Fina
void afterNoun()
{
    if(t_flag == true)
        cout << ("Processing <afterNoun>\n") << endl;

    switch(next_token())
    {
        case IS: 
        case WAS:
            be();
            gen("DESCRIPTION");
            gen("TENSE");
            match(PERIOD);
            outfile << endl;
            break;
        case DESTINATION:
            match(DESTINATION);
            gen("TO");
            verb();
            getEword();
            gen("ACTION");
            tense();
            gen("TENSE");
            match(PERIOD);
            outfile << endl;
            break;
        case OBJECT:
            match(OBJECT);
            gen("OBJECT");
            afterObject();
            break;
        default:
            syntaxerror2(saved_lexeme, "<afterNoun>");
    }
}
// Grammar: <afterSubject>::=<verb> #getEword# #gen(“ACTION”)# <tense> #gen(“TENSE”)# PERIOD | 
//                           <noun> #getEword#  <afterNoun>
// Done by: Ricardo Lizarraga
void afterSubject()
{
    if(t_flag == true)
        cout << "Processing <afterSubject>" << endl;  // print out the message mentioning the beginning of afterSubject parser function.
    switch(next_token())         // check next_token()
    {
       case WORD2:               // if next_token() is WORD2 meaning <verb> 
          verb();                // go to verb() function
          getEword();             //go to getEword() function
          gen("ACTION");        //Generate semantic routine "ACTION"
          tense();               // go to tense() function
          gen("TENSE");            //Generate semantic routine "TENSE"
          match(PERIOD);         // match PERIOD
          outfile << endl;
          break;                 // then break to get out of switch
       case WORD1:               // if next_token() is either WORD1 or PRONOUN
       case PRONOUN:             // which means <noun>
          noun();                // got to noun() function
          getEword();            //go to getEword() function
          afterNoun();         // go to afterNoun()
          break;                 // then break to get out of switch
       default:                  // otherwise,
          syntaxerror2(saved_lexeme, "afterSubject"); // go to syntaxerror2 to mention the error
    } // end of switch
}
// Grammar: <s>::=[CONNECTOR #getEword# #gen(“CONNECTOR”)#] <noun> #getEword# SUBJECT #gen(“ACTOR”)# <afterSubject>
// Done by: Chihiro Nishijima
void s()
{
   if(t_flag == true)
      cout << "Processing <s>" << endl;    // print out the message mentioning the beginning of s parser function.
   switch(next_token())         // check next_token()
   { 
      case CONNECTOR:          // if next_token() is CONNECTOR
         match(CONNECTOR);     // match CONNECTOR
         getEword();           // go to getEword() function
         gen("CONNECTOR");     // sematic routine: "CONNECTOR" line type
         noun();               // go to noun() function
         getEword();           // go to getEword() function
         match(SUBJECT);       // match SUBJECT
         gen("ACTOR");         // sematic routine: "ACTOR" line type
         afterSubject();       // go to afterSubject() function
         break;                // then break to get out of switch
      case WORD1:              // if next_token() is WORD1/PRONOUN meaning <noun>
      case PRONOUN:            
         noun();               // go to noun() function
         getEword();           // go to getEword() function
         match(SUBJECT);       // match SUBJECT
         gen("ACTOR");         // sematic routine: "ACTOR" line type
         afterSubject();       // go to afterSubject() function
         break;                // then break to get out of switch
      default:                 // otherwise,
         syntaxerror2(saved_lexeme, "s"); // go to syntaxerror2 to mention the error
   } // end of switch
}

// Grammar: <story>::=<s>{ <s> }
// Done by: Ricardo Lizarraga, Chihiro Nishijima
void story()
{
   if(t_flag == true)
      cout << "Processing <story>" << endl << endl; // print out the message mentioning the beginning of s parser function.
   s(); // go to s() function for <s>
   while(true)  // repeat loop 
   {
      if(saved_lexeme == "eofm") break;  // if the saved_token is end of the word, break the loop.
      switch(next_token())   // check next_token()
      {
         case CONNECTOR:     // if next_token() is CONNECTOR
         case WORD1:         // if next_token() is WORD1/PRONOUN meaning <noun>
         case PRONOUN:
            s();             // go to s() function
            break;           // then break to get out of switch
         case EOFM: break;   // if next_token() is EOFM, break the switch
         default:            // otherwise,
            syntaxerror2(saved_lexeme, "story"); // go to syntaxerror2 to mention the error
      } // end of switch
   } // end of while 
   
   if(t_flag == true)
      cout << endl << "Successfully parsed <story>." << endl;  // print out the story was parsed without any error. 
}
// ---------------- Driver ---------------------------

// The final test driver to start the translator
// Done by:  Chihiro Nishijima
int main()
{
  //** opens the lexicon.txt file and reads it into Lexicon
  ifstream infile;
  infile.open("lexicon.txt");
  string jap, eng;
  while(infile >> jap >> eng)
  {
     vector<string> row;
     row.push_back(jap);
     row.push_back(eng);
     dictionary.push_back(row);
  }
  //** closes lexicon.txt 
  infile.close();
  
  // Turn On/Off tracing messages
  while(true)
  {  
     string trace_input;
     cout << "Turn On the tracing messages (y/n): ";
     cin >> trace_input;
     if (trace_input == "y") // turn on the tracing message
     {
        t_flag = true;
        break;
     }
     else 
     if(trace_input == "n") // turn off the tracing massage
     {
        t_flag = false;
        break;
     }
  }
  
  //** opens the output file translated.txt
  outfile.open("translated.txt", ofstream::out | ofstream::trunc);
  errorfile.open("errors.txt", ofstream::out | ofstream::trunc);
  
  cout << "Enter the input file name: ";
  cin >> filename;
  fin.open(filename.c_str());

  //** calls the <story> to start parsing
  story();
  //** closes the input file 
  fin.close();
  //** closes traslated.txt
  outfile.close();
  errorfile.close();
 
}// end
//** require no other input files!
//** syntax error EC requires producing errors.txt of error messages
//** tracing On/Off EC requires sending a flag to trace message output functions


