#include <iostream>

using namespace std;

/*until we find an error or go through the entire text,
 * check that each bracket is closed by a bracket of the corresponding type;
 * we go through the text until we meet an open bracket,
 * then call the function recursively, remembering the type of the opening bracket, and read it
 * until we find a closing brackets, the type of which is comparable to the stored one,
 * or until we go beyond the text boundaries*/
void secondary_are_brackets_correct (bool &are_correct, char *text, int size, int &position, char brackets_type){
    char buffer;
    while ((are_correct == 1) && (position < size) && (text[position] != ')') && (text[position] != ']') && (text[position] != '}')){
        //cout << position << '\t' << brackets_type << '\t' << are_correct << '\n';
        switch (text[position]) {
            case '(':{
                secondary_are_brackets_correct(are_correct, text, size, ++position, '(');
                break;
            }    
            case '[':{
                secondary_are_brackets_correct(are_correct, text, size, ++position, '[');
                break;
            }    
            case '{':{
                secondary_are_brackets_correct(are_correct, text, size, ++position, '{');
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
    //cout << position << '\t' << brackets_type << '\t' << are_correct << '\n';
}

/*check that each opening bracket is followed by its corresponding closing and then call a secondary recursive check;
 * return the result*/
bool primary_are_brackets_correct (char *user_text, int text_size, char brackets_type){
    bool are_correct = 1;
    int cur_position = 0;
    int sqr_counter = 0;
    int rnd_counter = 0;
    int crl_counter = 0;

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

    secondary_are_brackets_correct(are_correct, user_text, text_size, cur_position, '-');

    return are_correct;
}


int main()
{
    int text_size;
    bool result;
    char *user_text = new char[text_size];

    cout << "Please, input size of your text:\n";
    cin >> text_size;
    cout << "Please, input your text:\n";
    cin >> user_text;

    result = primary_are_brackets_correct(user_text, text_size, '-');
    if (result == 1) cout << "BRACKETS ARE CORRECT!";
    if (result == 0) cout << "BRACKETS ARE NOT CORRECT!";

    delete user_text;
    return 0;
}