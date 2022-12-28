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

bool token_available;

// Type of error: Match fails
// Done by: Ricardo Lizarraga
void syntaxerror1(tokentype token_type, string saved_lexeme){
    cout << "SYNTAX ERROR: expected " << tokenName[token_type] << " but found " << saved_lexeme << endl;
    exit(1);
}

// Type of error: Switch default in a parser function
// Done by: Ricardo Lizarraga
void syntaxerror2(string saved_lexeme, string parser_function) {
    cout << "SYNTAX ERROR: unexpected " << saved_lexeme << " found in " << parser_function << endl;
    exit(1);
}

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
      cout << "Matched " << tokenName[saved_token] << endl;
      return true; // there was a match!!!
    }

}

// ----- RDP functions - one per non-term -------------------

// ** Make each non-terminal into a function here
// ** Be sure to put the corresponding grammar rule above each function
// ** Be sure to put the name of the programmer above each function


// Grammar: <tense>::=VERBPAST | VERBPASTNEG | VERB | VERBNEG
// Done by: Chihiro Nishijima
void tense()
{
   cout << "Processing <tense>" << endl;
   switch(next_token())
   {
      case VERBPAST:
         match(VERBPAST);
         break;
      case VERBPASTNEG:
         match(VERBPASTNEG);
         break;
      case VERB:
         match(VERB);
         break;
      case VERBNEG:
         match(VERBNEG);
         break;
      default:
         syntaxerror2(saved_lexeme, "tense");
   }
}
// Grammar: <be>::=IS | WAS
// Done by: Chihiro Nishijima
void be()
{
   cout << "Processing <be> " << endl;
   switch(next_token())
   {
      case IS: 
         match(IS);
         break;
      case WAS: 
         match(WAS);
         break;
      default:
         syntaxerror2(saved_lexeme, "be");
   }
}
// Grammar: <verb>::=WORD2
// Done by: Chihiro Nishijima
void verb()
{
   cout << "Processing <verb>" << endl;
   match(WORD2);
}
// Grammar: <noun>::=WORD1 | PRONOUN
// Done by: Chihiro Nishijima
void noun()
{
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
// Grammar: <afterObject>::=<verb> <tense> PERIOD | <noun> DESTINATION <verb> <tense> PERIOD
// Done by: Chihiro Nishijima
void afterObject()
{
    cout << "Processing <afterObject>" << endl;
    switch(next_token())
    {
       case WORD2:
          verb();
          tense();
          match(PERIOD);
          break;
       case WORD1:
       case PRONOUN:
          noun();
          match(DESTINATION);
          verb();
          tense();
          match(PERIOD);
          break;
       default:
          syntaxerror2(saved_lexeme, "afterObject");
    }     
}
// Grammar: <afterNoun>::=<be> PERIOD | DESTINATION <verb> <tense> PERIOD | OBJECT <afterObject>
// Done by: Chihiro Nishijima
void afterNoun()
{
   cout << "Processing <afterNoun>" << endl;
   switch(next_token())
   {
      case IS:
      case WAS:
         be();
         match(PERIOD);
         break;
      case DESTINATION:
         match(DESTINATION);
         verb();
         tense();
         match(PERIOD);
         break;
      case OBJECT:
         match(OBJECT);
         afterObject();
         break;
      default:
         syntaxerror2(saved_lexeme, "afterNoun");
   }             
}
// Grammar: <afterSubject>::=<verb> <tense> PERIOD | <noun> <afterNoun>
// Done by: Chihiro Nishijima
void afterSubject()
{
   cout << "Processing <afterSubject>" << endl;
   switch(next_token())
   {
      case WORD2:
         verb();
         tense();
         match(PERIOD);
         break;
      case WORD1:
      case PRONOUN:
         noun();
         afterNoun();
         break;
      default:
         syntaxerror2(saved_lexeme, "afterSubject");
   }
}
// Grammar: <s>::=[CONECTOR] <noun> SUBJECT <afterSubject>
// Done by: Chihiro Nishijima
void s()
{
   cout << "Processing <s>" << endl;
   switch(next_token())
   { 
      case CONNECTOR:
         match(CONNECTOR);
         break;
      case WORD1:
      case PRONOUN:
         break;
      default:
         break;
         //syntaxerror2(saved_lexeme, "s");
   }
   noun();
   match(SUBJECT);
   afterSubject();
}
// Grammar: <story>::=<s>{<s>}
// Done by: Chihiro Nishijima
void story()
{
   cout << "Processing <story>" << endl << endl;
   s();
   while(true)
   {
      if(saved_lexeme == "eofm") break;
      switch(next_token())
      {
         case CONNECTOR:
         case WORD1:
         case PRONOUN:
            s();
            break;
         case EOFM: break;
         default:
            syntaxerror2(saved_lexeme, "story");
      }
   }  
   cout << endl << "Successfully parsed <story>." << endl;  
}


string filename;

//----------- Driver ---------------------------

// The new test driver to start the parser
// Done by:  Chihiro Nishijima
int main()
{
  cout << "Enter the input file name: ";
  cin >> filename;
  fin.open(filename.c_str());

  //** calls the <story> to start parsing
  story();
  fin.close(); // close the input file
  
}// end
//** require no other input files!
//** syntax error EC requires producing errors.txt of error messages
//** tracing On/Off EC requires sending a flag to trace message output functions
