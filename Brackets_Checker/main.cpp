#include <iostream>
#include <string>

using namespace std;

/*until we find an error or go through the entire text,
 * check that each bracket is closed by a bracket of the corresponding type;
 * we go through the text until we meet an open bracket,
 * then call the function recursively, remembering the type of the opening bracket, and read it
 * until we find a closing brackets, the type of which is comparable to the stored one,
 * or until we go beyond the text boundaries*/
void secondary_are_brackets_correct (bool &are_correct, string text, int &position, char brackets_type){
    int size = text.size();
    while ((are_correct == 1) && (position < size) && (text[position] != ')') && (text[position] != ']') && (text[position] != '}')){
        switch (text[position]) {
            case '(':{
                secondary_are_brackets_correct(are_correct, text, ++position, '(');
                break;
            }    
            case '[':{
                secondary_are_brackets_correct(are_correct, text, ++position, '[');
                break;
            }    
            case '{':{
                secondary_are_brackets_correct(are_correct, text, ++position, '{');
                break;
            }    
            default:{
                break;
            }
        }
        position++;
    }


    if (position < size){
        if ((text[position] == ')') && (brackets_type != '(')) are_correct = 0;
        if ((text[position] == ']') && (brackets_type != '[')) are_correct = 0;
        if ((text[position] == '}') && (brackets_type != '{')) are_correct = 0;
    }
}

/*check that each opening bracket is followed by its corresponding closing and then call a secondary recursive check;
 * return the result*/
bool primary_are_brackets_correct (string user_text, char brackets_type){
    bool are_correct = 1;
    int cur_position = 0;
    int sqr_counter = 0;
    int rnd_counter = 0;
    int crl_counter = 0;
    int text_size = user_text.size();

    for (int i = 0; i < text_size; i++){
        if (user_text[i] == '(') rnd_counter++;
        if (user_text[i] == ')') rnd_counter--;
        if (user_text[i] == '[') sqr_counter++;
        if (user_text[i] == ']') sqr_counter--;
        if (user_text[i] == '{') crl_counter++;
        if (user_text[i] == '}') crl_counter--;
        if ((rnd_counter < 0) || (sqr_counter < 0) || (crl_counter < 0)) are_correct = 0;
    }
    if ((rnd_counter > 0) || (sqr_counter > 0) || (crl_counter > 0)) are_correct = 0;

    secondary_are_brackets_correct(are_correct, user_text, cur_position, '-');

    return are_correct;
}


int main()
{
    bool result;
    string user_text;

    cout << "Please, input your text:\n";
    getline(cin, user_text);

    result = primary_are_brackets_correct(user_text, '-');
    if (result == 1) cout << "BRACKETS ARE CORRECT!";
    if (result == 0) cout << "BRACKETS ARE NOT CORRECT!";

    return 0;
}