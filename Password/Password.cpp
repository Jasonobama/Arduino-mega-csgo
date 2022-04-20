/*
||
20200608整理openmaker——aced君
||
*/

#include "Password.h"

//construct object in memory, set all variables
Password::Password(char* pass){
	set( pass );
	reset();
}

//set the password
void Password::set(char* pass){
	target = pass;
}

//evaluate a string, is it equal to the password?
bool Password::is(char* pass){ 
	byte i=0;
	while (*pass && i<MAX_PASSWORD_LENGTH){
		guess[i] = pass[i];
		i++;
	}
	return evaluate();
}

//append a char to the guessed password
bool Password::append(char character){ 
	if (currentIndex+1==MAX_PASSWORD_LENGTH){
		return false;
	}else{
		guess[currentIndex++] = character;
		guess[currentIndex] = STRING_TERMINATOR; //ensure a valid c string
	}
	return true;
}

//reset the guessed password, one can guess again
void Password::reset(){ 
	currentIndex = 0;
	guess[currentIndex] = STRING_TERMINATOR;
}

//is the current guessed password equal to the target password?
bool Password::evaluate(){ 
	char pass = target[0];
	char guessed = guess[0];
	for (byte i=1; i<MAX_PASSWORD_LENGTH; i++){
		
		//check if guessed char is equal to the password char
		if (pass==STRING_TERMINATOR && guessed==STRING_TERMINATOR){
			return true; //both strings ended and all previous characters are equal 
		}else if (pass!=guessed || pass==STRING_TERMINATOR || guessed==STRING_TERMINATOR){
			return false; //difference OR end of string has been reached
		}
		
		//read next char
		pass = target[i];
		guessed = guess[i];
	}
	return false; //a 'true' condition has not been met
}

//set password using operator =
Password &Password::operator=(char* pass){
	set( pass );
	return *this;
}

//test password using ==
bool Password::operator==(char* pass){
	return is( pass );
}

//test password using !=
bool Password::operator!=(char* pass){
	return !is( pass );
}

//append to currently guessed password using operator <<
Password &Password::operator<<(char character){
	append( character );
	return *this;
}

/*

*/