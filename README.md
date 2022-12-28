# Japanese-English Translator - translator program


A simple translator program translating simple sentences from English/Japanese to Japanese/English.
coursework of CS 421

## Table of Contents
*[General Info](#general-info)
*[Features](#features)
*[Technologies](#technologies)
*[What I Learned](#what-I-learned)


## General info
This program allows to translate English and Japanese using DFA. 
Since this program is basic simple translator, words to be translated are limitted. 

## Features
This project is completed step by step. Starting with scanner.cpp, then myparser.cpp and the final version is group19project.cpp.
### scanner.cpp
scanner.cpp is for scanner code to match DFA (Deterministic finite automaton). 
Based on gramatical rules such as vowel, consonant and reserved words, program decide whether or not its is valid word or not.
### myparser.cpp
myparser.cpp is for parse code to determine grammer type based on the word scanned in scanner code.
### group19project.cpp
group19project.cpp is the final version of translator including all features of scanner and parser.  
Extra ability of:
 * Display each messages when a word is scanned and parsed in parser function.
 * Catch syntax error and recovery it.


## Technologies
Project is created with:
C++

## What I Learned
* DFA: Deterministic finite automata




