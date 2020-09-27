#include <stdio.h>
#include <string.h>
#include <string>
#include <ctype.h>
#include <conio.h>
#include <vector>
#include <iostream>
#include<cstdlib>
#include<fstream>

#define star 0 //*
#define slash 1 /*/*/
#define equal 2/*=*/
#define comma 3 /*,*/
#define semicolon 4 /*;*/
#define colon 5 /*:*/
#define point 6/*.*/
#define leftpar 9/*(*/
#define rightpar 10 /*)*/
#define later 11 /*<*/
#define greater 12 /*>*/
#define laterequal 13 /*<=*/
#define greaterequal 14 /*>=*/
#define plus 15 /*+*/
#define minus 16 /*-*/
#define slashequal 17 /*/=*/
#define assign 18 /*:=*/
#define commas 19 /*"*/

#define ident 20 /*идентификатор*/
#define floatc 21 /*вещ константа*/
#define intc 22 /*цел константа*/
#define charc 23 /*сим константа*/

#define elsesy 24
#define thensy 25
#define ifsy 26
#define endifsy 27
#define functionsy 28
#define proceduresy 29
#define beginsy 30
#define endsy 31
#define whilesy 32
#define whensy 33
#define loopsy 34
#define arraysy 35
#define orsy 36
#define andsy 37
#define ofsy 38
#define insy 39
#define issy 40
#define forsy 41
#define outsy 42
#define returnsy 43
#define withsy 44
#define Adasy 45
#define Text_IOsy 46
#define Integer_Text_IOsy 47
#define Integersy 48
#define floatsy 49
#define charsy 50

#define Putsy 51
#define Getsy 52
#define New_Linesy 53
#define abssy 54
#define sqrtsy 55
#define Float_Text_IOsy 56
#define Numericssy 57
#define Generic_Elementary_Functionssy 58
#define Packagesy 59
#define FL_Mathsy 60
#define newsy 61
#define elsifsy 62
#define usesy 63
#define xorsy 64
#define typesy 65
#define EOI 99

struct key
{
    unsigned codekey;
    char namekey [32];
} keywords1 [ ] =
    {ident, " "},
keywords2 [ ] =
{
    {ifsy, "if"},
    {issy, "is"},
    {insy, "in"},
    {ofsy, "of"},
    {orsy, "or"}
},
 keywords3 [ ] =
{
    {forsy, "for"},
    {outsy, "out"},
    {endsy, "end"},
    {Adasy, "Ada"},
    {Putsy, "Put"},
    {Getsy, "Get"},
    {abssy, "abs"},
    {newsy, "new"},
    {usesy, "use"},
    {andsy, "and"},
    {xorsy, "xor"}
},
keywords4 [] =
{
    {withsy, "with"},
    {charsy, "char"},
    {sqrtsy, "sqrt"},
    {thensy, "then"},
    {elsesy, "else"},
    {loopsy, "loop"},
    {typesy, "type"}
},
keywords5 [ ] =
{
    {beginsy, "begin"},
    {endifsy, "endif"},
    {floatsy, "float"},
    {elsifsy, "elsif"},
    {whilesy, "while"},
    {arraysy, "array"}
},
keywords6 [ ] =
{
    {returnsy, "return"}
},
keywords7 [ ] =
{
    {Text_IOsy, "Text_IO"},
    {Integersy, "Integer"},
    {Packagesy, "package"},
    {FL_Mathsy, "FL_Math"}
},
keywords8 [ ] =
{
    {functionsy, "function"},
    {New_Linesy, "New_Line"},
    {Numericssy, "Numerics"}
},
keywords9 [ ] =
{
    {proceduresy, "procedure"}
},
keywords13 [ ] =
{
    {Float_Text_IOsy, "Float_Text_IO"}
},
keywords15 [ ] =
{
    {Integer_Text_IOsy, "Integer_Text_IO"}
},
keywords28 [ ] =
{
    {Generic_Elementary_Functionssy, "Generic_Elementary_Functions"}
};


int n1=14;
char *splitter[14]={".",",",";","(",")","/","*","+","-","\"","<=",">=",":=","/="};//????
int n2=4;
char *word[4]={"begin","end","with","procedure"};
using namespace std;
class lekser
{
private:
    FILE *f_in, *f_out;
    key lexem;
    char c;
public:
    lekser()
    {
        f_in=fopen("in.txt","r");
        if (f_in==NULL) return;
        f_out=fopen("out.txt","w");
        if (f_out==NULL) return;
    }
    void printer (char *name, int code)
    {
        //cout <<name<<" "<<code<<endl;
        fprintf (f_out,"%s %d\n",name, code);
        lexem.codekey=code;
        strcpy(lexem.namekey,name);
    }
    void read()
    {
        bool j=1;
      do
      {
          if (j)
            c=fgetc(f_in);
          else j=1;

          if (c>=48&&c<=57)
             c=number (c);
          if (c>=65&&c<=90||c>=95&&c<=122)
             c=words(c);
          if (c>=40&&c<=47||c>=58&&c<=62||c==34)
             c=znaks(c,&j);
            //cout<<c<<" zn"<<endl;
      }  while (c!=EOF);
      fprintf (f_out,"EOF %d\n",EOI);
    }
    char number(char c)//считывание цифр
    {
        int i=0;
        bool j=1,k=0;
        char name_n[32]="";
        name_n[i]=c;
        do
        {
            c=getc(f_in);
            if ((c>=48&&c<=57||c==46)&&i<9)
            {
               if (c==46)
                {
                    if (!k)
                    {
                        i++;
                        name_n[i]=c;
                        k=1;
                    }
                    else cout<<"error_float_......"<<endl;
                }
                else
                {
                    i++;
                    name_n[i]=c;
                }
            }
            else j=0;
        } while (j);
        //fprintf (f_out,"%s %d\n",name_n,intc);
        if (k==1)
            printer(name_n,floatc);
        else
            printer (name_n,intc);
        return c;
    }
    char words(char c)
    {
        char name_w[32]="";
        int i=0, k=0, l=0;
        bool j=1;
        name_w[i]=c;
        do
        {
            c=getc(f_in);
            if (c>=65&&c<=90||c>=95&&c<=122||c>=48&&c<=57)
            {
                i++;
                name_w[i]=c;
            }
            else j=0;
        }while (j);
        j=1;
        switch (strlen(name_w))
        {
        case 2: k=sizeof(keywords2)/sizeof(*keywords2);
            for (i=0;i<k;i++)
            if (!strcmp(keywords2[i].namekey,name_w))
                {
                    //fprintf (f_out,"%s %d\n",keywords2[i].namekey,keywords2[i].codekey);
                    printer (keywords2[i].namekey,keywords2[i].codekey);
                    j=0;
                    break;
                }
                if (j) //fprintf (f_out,"%s %d\n",name_w,keywords1[0].codekey);
                    printer (name_w,keywords1[0].codekey);
            break;
        case 3: k=sizeof(keywords3)/sizeof(*keywords3);
            for (i=0;i<k;i++)
            if (!strcmp(keywords3[i].namekey,name_w))
                {
                    if (keywords3[i].codekey!=Adasy&&keywords3[i].codekey!=newsy&&keywords3[i].codekey!=usesy)
                        //fprintf (f_out,"%s %d\n",keywords3[i].namekey,keywords3[i].codekey);
                        printer (keywords3[i].namekey,keywords3[i].codekey);
                    j=0;
                    if (keywords3[i].codekey==usesy)
                        while (c!='\n')
                        c=fgetc(f_in);
                    break;
                }
                if (j) //fprintf (f_out,"%s %d\n",name_w,keywords1[0].codekey);
                    printer (name_w,keywords1[0].codekey);
            break;
        case 4: k=sizeof(keywords4)/sizeof(*keywords4);
            for (i=0;i<k;i++)
            if (!strcmp(keywords4[i].namekey,name_w))
                {
                    if (keywords4[i].codekey!=withsy)
                        //fprintf (f_out,"%s %d\n",keywords4[i].namekey,keywords4[i].codekey);
                        printer (keywords4[i].namekey,keywords4[i].codekey);
                    if (keywords4[i].codekey==withsy)
                        while (c!='\n')
                        c=fgetc(f_in);
                    j=0;

                    break;
                }
                if (j) //fprintf (f_out,"%s %d\n",name_w,keywords1[0].codekey);
                    printer (name_w,keywords1[0].codekey);
            break;
        case 5: k=sizeof(keywords5)/sizeof(*keywords5);
            for (i=0;i<k;i++)
            if (!strcmp(keywords5[i].namekey,name_w))
                {
                    //fprintf (f_out,"%s %d\n",keywords5[i].namekey,keywords5[i].codekey);
                    printer (keywords5[i].namekey,keywords5[i].codekey);
                    j=0;
                    break;
                }
                if (j) //fprintf (f_out,"%s %d\n",name_w,keywords1[0].codekey);
                    printer (name_w,keywords1[0].codekey);
            break;
        case 6: k=sizeof(keywords6)/sizeof(*keywords6);
            for (i=0;i<k;i++)
            if (!strcmp(keywords6[i].namekey,name_w))
                {
                    //fprintf (f_out,"%s %d\n",keywords6[i].namekey,keywords6[i].codekey);
                    printer (keywords6[i].namekey,keywords6[i].codekey);
                    j=0;
                    break;
                }
                if (j) //fprintf (f_out,"%s %d\n",name_w,keywords1[0].codekey);
                    printer (name_w,keywords1[0].codekey);
            break;
        case 7: k=sizeof(keywords7)/sizeof(*keywords7);
            for (i=0;i<k;i++)
            if (!strcmp(keywords7[i].namekey,name_w))
                {
                    if (keywords7[i].codekey!=Text_IOsy&&keywords7[i].codekey!=Packagesy&&keywords7[i].codekey!=FL_Mathsy)
                    //fprintf (f_out,"%s %d\n",keywords7[i].namekey,keywords7[i].codekey);
                    printer (keywords7[i].namekey,keywords7[i].codekey);
                    if (keywords7[i].codekey==Packagesy)
                    {
                        while (c!='\n')
                            c=getc(f_in);
                    }
                    j=0;
                    break;
                }
                if (j) //fprintf (f_out,"%s %d\n",name_w,keywords1[0].codekey);
                    printer (name_w,keywords1[0].codekey);
            break;
        case 8: k=sizeof(keywords8)/sizeof(*keywords8);
            for (i=0;i<k;i++)
            if (!strcmp(keywords8[i].namekey,name_w))
                {
                    if (keywords8[i].codekey!=Numericssy)
                    //fprintf (f_out,"%s %d\n",keywords8[i].namekey,keywords8[i].codekey);
                    printer (keywords8[i].namekey,keywords8[i].codekey);
                    j=0;
                    break;
                }
                if (j) //fprintf (f_out,"%s %d\n",name_w,keywords1[0].codekey);
                    printer (name_w,keywords1[0].codekey);
            break;
        case 9: k=sizeof(keywords9)/sizeof(*keywords9);
            for (i=0;i<k;i++)
            if (!strcmp(keywords9[i].namekey,name_w))
                {
                    //fprintf (f_out,"%s %d\n",keywords9[i].namekey,keywords9[i].codekey);
                    printer (keywords9[i].namekey,keywords9[i].codekey);
                    j=0;
                    break;
                }
                if (j) //fprintf (f_out,"%s %d\n",name_w,keywords1[0].codekey);
                    printer (name_w,keywords1[0].codekey);
            break;
        case 13: k=sizeof(keywords13)/sizeof(*keywords13);
            for (i=0;i<k;i++)
            if (!strcmp(keywords13[i].namekey,name_w))
                {
                    //fprintf (f_out,"%s %d\n",keywords13[i].namekey,keywords13[i].codekey);
                    j=0;
                    break;
                }
                if (j) //fprintf (f_out,"%s %d\n",name_w,keywords1[0].codekey);
                    printer (name_w,keywords1[0].codekey);
            break;
        case 15: k=sizeof(keywords15)/sizeof(*keywords15);
            for (i=0;i<k;i++)
            if (!strcmp(keywords15[i].namekey,name_w))
                {
                    //fprintf (f_out,"%s %d\n",keywords15[i].namekey,keywords15[i].codekey);
                    j=0;
                    break;
                }
                if (j) //fprintf (f_out,"%s %d\n",name_w,keywords1[0].codekey);
                    printer (name_w,keywords1[0].codekey);
            break;
        case 28: k=sizeof(keywords28)/sizeof(*keywords28);
            for (i=0;i<k;i++)
            if (!strcmp(keywords28[i].namekey,name_w))
                {
                    //fprintf (f_out,"%s %d\n",keywords28[i].namekey,keywords28[i].codekey);
                    j=0;
                    break;
                }
                if (j) //fprintf (f_out,"%s %d\n",name_w,keywords1[0].codekey);
                    printer (name_w,keywords1[0].codekey);
            break;
        default: //fprintf (f_out,"%s %d\n",name_w,keywords1[0].codekey);
                   printer (name_w,keywords1[0].codekey);
            break;
        }

        if (c!='.')
            return c;
        else
        {
            c=' ';
            return c;
        }
    }
    char znaks(char c,bool *j)
    {
        char name_z[2]="", nm[2]="0";
        name_z[0]=c;
        switch (name_z[0])
        {
            case '*':
                //fprintf (f_out,"%s %d\n",name_z,star);
                printer (name_z,star);
                break;
            case '=':
               // fprintf (f_out,"%s %d\n",name_z,equal);
               printer (name_z,equal);
                break;
            case '.':
                //fprintf (f_out,"%s %d\n",name_z,point);
                printer (name_z,point);
                break;
            case '(':
                //fprintf (f_out,"%s %d\n",name_z,leftpar);
                printer (name_z,leftpar);
                break;
            case ')':
                //fprintf (f_out,"%s %d\n",name_z,rightpar);
                printer (name_z,rightpar);
                break;
            case '+':
                //fprintf (f_out,"%s %d\n",name_z,plus);
                printer (name_z,plus);
                break;
            case '"':
                //fprintf (f_out,"%s %d\n",name_z,commas);
                printer (name_z,commas);
                break;
            case ';':
                //fprintf (f_out,"%s %d\n",name_z,semicolon);
                printer (name_z,semicolon);
                break;
        }
        if (name_z[0]=='>')
        {
            c=fgetc(f_in);
            if (c=='=')
            {
                name_z[1]='=';
                name_z[2]='\0';
                //fprintf (f_out,"%s %d\n",name_z,greaterequal);
                printer (name_z,greaterequal);
            }
            else
            {
                *j=0;
                //fprintf (f_out,"%s %d\n",name_z,greater);
                printer (name_z,greater);
            }
        }
        if (name_z[0]=='<')
        {
            c=fgetc(f_in);
            if (c=='=')
            {
                name_z[1]='=';
                name_z[2]='\0';
                fprintf (f_out,"%s %d\n",name_z,laterequal);
                printer (name_z,laterequal);
            }
            else
            {
                *j=0;
                //fprintf (f_out,"%s %d\n",name_z,later);
                printer (name_z,later);
            }
        }
        if (name_z[0]=='/')
        {
            c=fgetc(f_in);
            if (c=='=')
            {
                name_z[1]='=';
                name_z[2]='\0';
                //fprintf (f_out,"%s %d\n",name_z,slashequal);
                printer (name_z,slashequal);
            }
            else
            {
                *j=0;
                //fprintf (f_out,"%s %d\n",name_z,slash);
                printer (name_z,slash);
            }
        }
        if (name_z[0]==':')
        {
            c=fgetc(f_in);
            if (c=='=')
            {
                name_z[1]='=';
                name_z[2]='\0';
                //fprintf (f_out,"%s %d\n",name_z,assign);
                printer (name_z,assign);
            }
            else
            {
                *j=0;
                //fprintf (f_out,"%s %d\n",name_z,colon);
                printer (name_z,colon);
            }
        }
        if (name_z[0]=='-')
        {
            c=fgetc(f_in);
            if (c=='-')
            {
                while (c!='\n')
                    c=fgetc(f_in);
            }
            else
            {
                *j=0;
                //fprintf (f_out,"%s %d\n",name_z,minus);
                if (lexem.codekey!=assign&&lexem.codekey!=leftpar&&lexem.codekey!=equal)
                    printer (name_z,minus);
                else
                {
                    printer ("0",intc);
                    printer (name_z, minus);
                }
            }
        }
        return c;
    }
    ~lekser()
    {
        fclose(f_in);
        fclose(f_out);
    }
};


enum { VAR, CST, ADD, SUB, MLT, DIV, LT, SET,
       IF1, IF2, WHILE, DO, EMPTY, SEQ, EXPR, PROG, GET, PRINT, OR, XOR, AND, SQRT, ABS, LET,ARR, MAINE, FUN, FUN1, FUN2};
    struct node
    {
        struct node *o1, *o2, *o3;
        int kind;
        key value;
    };
class parser
{
    public:

    FILE *f_in;
    key token,t_st[64],t_ar[10],t_fun[10],tkn;
    int i,j,k,l,m,pr,n;
    public:
    parser ()
    {
        f_in=fopen("out.txt","r");
        if (f_in==NULL) {cout<<"file_ups"<<endl; return;}
        i=j=k=l=m=n=0;
        pr = 1;
        token.codekey=-1;
        //program();
    }
    ~parser ()
    {
        fclose(f_in);
    }
    void syntax_error() { fprintf(stderr, "syntax error\n");  }
    void read()
    {
        delete token.namekey;
        fscanf(f_in,"%s ",token.namekey);
        l=strlen(token.namekey);
        token.namekey[l]='\0';
        fscanf(f_in,"%d",&token.codekey);
        //if (token.codekey==leftpar)pr =1;
        if (token.codekey==rightpar)
            pr = 0;
        //cout<<token.namekey<<" "<<token.codekey<<endl;
    }
    node* new_node(int k)
    {
        node* x=new node;
        x->kind=k;
        x->value=token;
        x->o1=NULL;
        x->o2=NULL;
        x->o3=NULL;
        return x;
    }
    node *term()  /* <term> ::= <id> | <int> | <paren_expr> */
    {
        node *x;

        if (token.codekey == ident)
        {

            x=new_node(VAR);
            x->value=token;
            if (!checkid(token))
                cout<<"error_not found id - "<<token.namekey<<endl;
            else if (checkid(token)==2)
            {
                read();
                if (token.codekey!=leftpar) cout<<"error_array_leftpar"<<token.namekey<<endl;
                read();
                if (token.codekey==intc||token.codekey==ident)
                {
                    x->o3=new_node(VAR);
                    x->o3->value=token;
                }
                else cout<<"error_array_NUMBER - "<<token.namekey<<endl;
                read();
                if (token.codekey!=rightpar) cout<<"error_array_rightpar"<<token.namekey<<endl;
            }
            else if (checkid(token)==3)
            {
                read();
                if (token.codekey!=leftpar) cout<<"error_array_leftpar"<<token.namekey<<endl;
                read();
                if (token.codekey==intc||token.codekey==ident)
                {
                    x->o3=new_node(VAR);
                    x->o3->value=token;
                }
                else cout<<"error_array_NUMBER - "<<token.namekey<<endl;
                read();
                if (token.codekey!=rightpar) cout<<"error_array_rightpar"<<token.namekey<<endl;
            }
            read();
        }
        else
            if (token.codekey == intc)
            {
                x=new_node(CST);
                x->value=token;
                read();
            }
            else
                if (token.codekey == floatc)
                {
                    x=new_node(CST);//??
                    x->value=token;
                    read();
                }
                else
                x = paren_expr();
        return x;
    }
    node *sum()  /* <sum> ::= <term> | <sum> "+" <term> | <sum> "-" <term> *///??????????????????????????????????????
    {
        node *t, *x = term(),*q;
        while (token.codekey == plus || token.codekey == minus||token.codekey == star || token.codekey == slash)
        {
            t=x;
            cout<<x->value.namekey<<endl;
            if (token.codekey==plus||token.codekey==minus)
                x=new_node(token.codekey==plus?ADD:SUB);
            else x=new_node(token.codekey==star?MLT:DIV);
            read();
            if (x->value.codekey == plus || x->value.codekey == minus)
            {
                x->o1=t;
                x->o2=term();
            }

            if (x->value.codekey == star || x->value.codekey == slash)
            {
                    if (t->o2!=NULL&&pr)
                    {
                        q=x;
                        if (t->value.codekey==star||t->value.codekey==slash)
                        {

                            x->o1=t;
                            x->o2=term();
                            if (!pr) pr=1;
                        }
                        else
                        {

                            q->o1=t->o2;
                            q->o2=term();
                            t->o2=q;
                            x=t;
                        }

                    }
                    else
                    {
                        x->o1=t;
                        x->o2=term();
                        if (!pr) pr=1;
                    }
            }
        }
      return x;
    }

    node *test()  /* <test> ::= <sum> | <sum> "<" <sum> */
    {
        node *t, *x = sum();
        if (token.codekey == later||token.codekey ==greater||token.codekey ==laterequal||token.codekey ==greaterequal||token.codekey ==equal)
        {
            t=x;
            x=new_node(LT);
            read();
            x->o1=t;
            x->o2=sum();
        }
        return x;
    }

    node *expr()  /* <expr> ::= <test> | <id> ":=" <expr> */
    {
        node *t, *x;

        if (token.codekey != ident)
            return test();

        x = test();
        if (x->kind == VAR && token.codekey == assign)
        {
            t=x;
            x=new_node(SET);
            read();
            x->o1=t;
            x->o2=expr();
        }
      return x;
    }

    node *paren_expr()
    {

        node *x, *t;
        if (token.codekey == leftpar||token.codekey == orsy||token.codekey == xorsy||token.codekey == andsy)
            read();
        else {cout<<"error_leftpar-( "<<token.namekey<<endl;syntax_error();}
            x = expr();

        if (token.codekey == rightpar||token.codekey == orsy||token.codekey == xorsy||token.codekey == andsy)
        {
            if (token.codekey == rightpar)
            read();
            else
            {
                if (token.codekey==orsy)
                    t=new_node(orsy);
                else if (token.codekey==andsy)
                        t=new_node(andsy);
                    else t=new_node(xorsy);
                t->o1=x;
                x=t;
                t->o2=expr();
            }
        }
        else {cout<<"error_rightpar-) "<<token.namekey<<endl;syntax_error();}
          return x;
    }

    node *statement()
    {
        pr=1;
        node *t, *x;

        switch (token.codekey)
        {
            case ifsy:
                    x = new_node(IF1);
                    read();
                    x->o1 = expr();
                    if (token.codekey!=thensy)
                    {
                        if (token.codekey==orsy||token.codekey==andsy||token.codekey==xorsy)
                        {
                            do
                            {
                                if (token.codekey==orsy)
                                    t=new_node(orsy);
                                    else if (token.codekey==andsy)
                                        t=new_node(andsy);
                                        else t=new_node(xorsy);
                                t->o1=x->o1;
                                x->o1=t;
                                read();
                                t->o2=expr();
                            }while (token.codekey!=thensy);
                             read();
                        }
                        else
                        {
                            cout<<"error_if-THEN"<<token.codekey<< " "<<token.namekey<<endl;
                            syntax_error();
                        }
                    }
                    else read();
                    x->o2 = statement();
                    if (token.codekey == elsesy)  /* ... "else" <statement> */
                    {
                        x->kind = IF2;
                        read();
                        x->o3 = statement();
                    }
                    if (token.codekey == elsifsy)
                    {
                        x->kind = IF1;
                        token.codekey=ifsy;
                        x->o3 = statement();
                    }
                break;
            case whilesy:
                    x = new_node(WHILE);
                    read();
                    x->o1 = expr();
                    if (token.codekey!=loopsy)
                    {
                        if (token.codekey==orsy||token.codekey==andsy||token.codekey==xorsy)
                        {
                            do
                            {
                                if (token.codekey==orsy)
                                    t=new_node(orsy);
                                    else if (token.codekey==andsy)
                                        t=new_node(andsy);
                                        else t=new_node(xorsy);
                                t->o1=x->o1;
                                x->o1=t;
                                read();
                                t->o2=expr();
                            } while (token.codekey!=loopsy);
                            if (token.codekey!=loopsy)
                            {
                                cout<<"error_while-LOOP"<<token.codekey<< " "<<token.namekey<<endl;
                                syntax_error();
                            }
                            else read();
                        }
                        else
                        {
                            cout<<"error_while-LOOP"<<token.codekey<< " "<<token.namekey<<endl;
                            syntax_error();
                        }
                    }
                        //cout<<"error_while-LOOP "<<token.codekey<< " "<<token.namekey<<endl;
                    else read();
                    x->o2 = statement();
                break;
            case semicolon:
                    x = new_node(EMPTY); read();
                break;
            case beginsy:
                    x = new_node(EMPTY);
                    read();
                    while (token.codekey != endsy)
                    {
                        t=x;
                        x=new_node(SEQ);
                        x->o1=t;
                        x->o2=statement();
                    }
                    read();

                    /*if (token.codekey!=EOI)
                        x->o3=statement();*/
                    //if (token.codekey!=loopsy||token.codekey!=ifsy||token.codekey!=ident)
                break;
            case SQRT://??
                    x= new_node(SQRT);
                    read();
                    x->o1=paren_expr();
                    if (token.codekey!=semicolon){cout<<"error_SQRT-; "<<token.codekey<< " "<<token.namekey<<endl; syntax_error();}
                    read();
                break;
            case ABS:
                    x= new_node(ABS);
                    read();
                    x->o1=paren_expr();
                    if (token.codekey!=semicolon){cout<<"error_ABS-; "<<token.codekey<< " "<<token.namekey<<endl; syntax_error();}
                    read();
                break;
            case Putsy:
                    x= new_node(PRINT);
                    read();
                    x->o1=paren_expr();
                    if (token.codekey!=semicolon){cout<<"error_Put-; "<<token.codekey<< " "<<token.namekey<<endl; syntax_error();}
                    read();
                break;
            case Getsy:
                    x= new_node(GET);
                    read();
                    x->o1=paren_expr();
                    if (token.codekey!=semicolon){cout<<"error_Get-; "<<token.codekey<< " "<<token.namekey<<endl; syntax_error();}
                    read();
                break;
            default:
                    x = new_node(EXPR);
                    x->o1 = expr();
                    if (token.codekey == semicolon)
                        read();
                    else
                        {cout<<"error_expr"<<token.codekey<< " "<<token.namekey<<endl; syntax_error();}
                break;
        }
      return x;
    }
    int checkid (key lex)
    {
        i=0;
        for (i=0;i<n;i++)//переменная
        {
            if (!strcmp(lex.namekey,t_st[i].namekey))
            return 1;
        }
        for (i=0;i<m;i++)//массив
        {
            if (!strcmp(lex.namekey,t_ar[i].namekey))
            return 2;
        }
        for (i=0;i<l;i++)
        {
            if (!strcmp(lex.namekey,t_fun[i].namekey))
            return 3;
        }
        return 0;
    }
    node *objav()
    {
        node *x, *t, *q;
         t=new_node(LET);
         x=t;
        while (token.codekey!=beginsy)
        {
            if (token.codekey==typesy)
            {
                t->o1=new_node(ARR);
                q=new_node(VAR);
                t->o1->o1=q;
                read();
                if (token.codekey!=ident) cout<<"error_array_IDENT-"<<token.namekey<<endl;
                t_ar[m]=token;
                m++;
               // t->o1->o1->value=t_ar[m-1];
                read();
                if (token.codekey!=issy) cout<<"error_array_IS - "<<token.namekey<<endl;
                read();
                if (token.codekey!=arraysy) cout<<"error_array_ ARRAY - "<<token.namekey<<endl;
                read();
                if (token.codekey!=leftpar) cout<<"error_array_LEFTPAR - "<<token.namekey<<endl;
                read();
                if (token.codekey!=intc) cout<<"error_array_()_INT - "<<token.namekey<<endl;
                q=new_node(ARR);
                t->o1->o3=q;
                q=new_node(VAR);
                t->o1->o3->o1=q;
                read();
                if (token.codekey!=point) cout<<"erro_array_()_POINT - "<<token.namekey<<endl;
                read();
                if (token.codekey!=point) cout<<"erro_array_()_POINT - "<<token.namekey<<endl;
                read();
                if (token.codekey!=intc) cout<<"error_array_()_INT - "<<token.namekey<<endl;
                q=new_node(VAR);
                t->o1->o3->o2=q;
                read();
                if (token.codekey!=rightpar) cout<<"error_array_RIGHTPAR - "<<token.namekey<<endl;
                read();
                if (token.codekey!=ofsy) cout<<"error_array_OF - "<<token.namekey<<endl;
                read();
                if (token.codekey!=Integersy&&token.codekey!=floatsy&&token.codekey!=charsy)
                    cout<<"error_array_TYPE - "<<token.namekey<<endl;
                t->o1->o2=new_node(VAR);
                read();
                if(token.codekey!=semicolon) cout<<"error_semicolon - "<<token.namekey<<endl;
                //if (n-1==0)x=t;
                t->o2=new_node(LET);
            }
            else
            {
                while (token.codekey!=semicolon)
                {

                    if (token.codekey==ident)
                    {
                        t_st[n]=token;
                        n++;
                    }
                    else if (token.codekey==Integersy||token.codekey==floatsy||token.codekey==charsy)
                        tkn=token;
                        else if (token.codekey!= colon) cout<<"error _ colon_:"<<endl;
                    read();
                }
                t->o1=new_node(LET);
                t->o1->o1=new_node(VAR);
                t->o1->o1->value=t_st[n-1];
                t->o1->o2=new_node(VAR);
                t->o1->o2->value=tkn;
                //if (n-1==0)x=t;
                t->o2=new_node(LET);
                t=t->o2;
            }
            read();
        }
        return x;
    }

    node *objav_param()
    {
        node *x, *t, *q;
        key qq;
         t=new_node(LET);
         x=t;
        while (token.codekey!=rightpar)
        {
            while (token.codekey!=semicolon)
            {
                if (token.codekey==ident)
                {
                    t_st[n]=token;
                    n++;
                    t->o1=new_node(LET);
                    t->o1->o1=new_node(VAR);
                    t->o1->o1->value=t_st[n-1];
                }
                else if (token.codekey==Integersy||token.codekey==floatsy||token.codekey==charsy)
                    {
                        cout<<token.namekey<<endl;
                    }
                    else if (token.codekey!= colon) cout<<"error _ colon_:"<<token.namekey<<endl;
                        else {read();if (token.codekey==insy) read();}
                read();
            }
            t->o1->o2=new_node(VAR);
            t->o1->o2->value.codekey==floatsy;
            strcpy(t->o1->o2->value.namekey,"float");

            //if (n-1==0)x=t;
            t->o2=new_node(LET);
            t=t->o2;
            read();
        }
        //n=0;
        return x;
    }
    node *fn()
    {
        node *x = new_node(FUN);
        node *t;
        if (token.codekey!=proceduresy&&token.codekey!=functionsy)
            {cout<<"error_function_procedure_ "<<token.codekey<< " "<<token.namekey<<endl; syntax_error();}
        read();
        if (token.codekey!=ident) {cout<<"error_function_procedure-ID_ "<<token.codekey<< " "<<token.namekey<<endl; syntax_error();}
        else
        {
            x->o2=new_node(FUN);
            t_fun[l]=token;
            l++;
            read();
        }
        if (token.codekey!=leftpar) {cout<<"error_function_procedure-(_ "<<token.codekey<< " "<<token.namekey<<endl; syntax_error();}
            read();
        while (token.codekey!=rightpar)
        {
            x->o2->o1=objav_param();
        }
        read();
        if (token.codekey!= issy) {cout<<"error_function_procedure-IS "<<token.codekey<< " "<<token.namekey<<endl; syntax_error();}
        else read();
        //if (token.codekey==proceduresy) {x->o3 = fn();read();}
        while (token.codekey!=beginsy)
        {
            if (token.codekey==proceduresy||token.codekey==functionsy)
                x->o3=fn();
            else
            {
                if (token.codekey==ident||token.codekey==typesy)
                {
                    i=0;
                    x->o2->o2=objav();
                }
            }
            if (token.codekey!=beginsy)
            read();
        }
        x->o1 = statement();
        return x;
    }
    node *program()  /* <program> ::= <statement> */
    {
        read();
        node *x = new_node(PROG);
        node *t;
        if (token.codekey!=proceduresy&&token.codekey!=functionsy)
            {cout<<"error_function_procedure_ "<<token.codekey<< " "<<token.namekey<<endl; syntax_error();}
        read();
        if (token.codekey!=ident) {cout<<"error_function_procedure-ID_ "<<token.codekey<< " "<<token.namekey<<endl; syntax_error();}
        else
        {
            x->o2=new_node(PROG);
            read();
        }
        if (token.codekey!=leftpar) {cout<<"error_function_procedure-(_ "<<token.codekey<< " "<<token.namekey<<endl; syntax_error();}
            read();
        while (token.codekey!=rightpar)
        {
            read();
        }
        read();
        if (token.codekey!= issy) {cout<<"error_function_procedure-IS "<<token.codekey<< " "<<token.namekey<<endl; syntax_error();}
        read();
        //if (token.codekey==proceduresy) {x->o3 = fn();read();}
        while (token.codekey!=beginsy)
        {
            if (token.codekey==proceduresy||token.codekey==functionsy)
                x->o3=fn();
            else
            {
                if (token.codekey==ident||token.codekey==typesy)
                {
                    i=0;
                    x->o2->o2=objav();
                }
            }
            if (token.codekey!=beginsy)
            read();
        }
        t=new_node(MAINE);
        t ->o1= statement();
        x->o1=t;

        if (token.codekey != EOI)
            {cout<<"error_eof "<<token.codekey<< " "<<token.namekey<<endl; syntax_error();}
        return x;
    }

};
class emitter
{
protected:
    FILE *data,*includ,*code;
    char Name[20];
    int Count_cnst=0,all=0;
    int count_var=0;
    string Naming[30];
public:
    emitter ()
    {
        strcpy(Name, "Number");
        start();
    }
    void start()
    {
        data=fopen("data.txt","w");
        includ=fopen("includ.txt","w");
        code=fopen("code.txt","w");
        fprintf(includ,".386\n\
    .model flat,stdcall\n\
    include\\masm32\\include\\masm32rt.inc\n\
    include\\masm32\\include\\msvcrt.inc\n\
    include\\masm32\\include\\kernel32.inc\n\
    includelib \\lib\masm32.lib\n\
    includelib \\lib\msvcrt.lib\n\
    includelib \\lib\kernel32.lib ");
    cout<<"check"<<endl;


    fprintf(data,".data \n");
    fprintf(code,".code \n");
    }

    void c(node *x)
    {
        cout<<" c "<<x->kind<<" "<<x->value.namekey<<endl;
        switch (x->kind)
        {
            case PROG : cout<<" PROG "<<x->kind<<" "<<x->value.namekey<<endl;
                if (x->o3) c(x->o3);
                c(x->o2); if (x->o1) c(x->o1); break;
            case SEQ  : cout<<" SEQ "<<x->kind<<" "<<x->value.namekey<<endl;
                c(x->o2); c(x->o1); break;
            case EXPR : cout<<" EXPR "<<x->kind<<" "<<x->value.namekey<<endl;
                if(x->o1->kind==SET)
                {
                    var_2(x->o1->o2);
                    fprintf(code,"pop ebx\n",x->o1->value.namekey);
                    fprintf(code,"mov %s,ebx\n",x->value.namekey);
                    fprintf(code,"push %s\n",x->value.namekey);
                    fprintf(code,"fld dword ptr[esp]\n",x->value.namekey);
                    fprintf(code,"call writefloat\n",x->value.namekey);
                    break;
                }
                else if(x->o1->kind==FUN1)
                    {c(x->o1);cout<<"ROCK"<<endl;
                    break;}
            case LET: cout<<" LET "<<x->kind<<" "<<x->value.namekey<<endl;
                var_1(x);
                    break;
            case IF1: cout<<"if1"<<endl;
                 fprintf(code,"mov eax,%s \n",x->o1->o1->value.namekey);
                 fprintf(code,"mov ebx,%s\n",x->o1->o2->value.namekey);
                 fprintf(code,".IF ");
                 IF_test(x->o1);
                 c(x->o2);
                 fprintf(code,".ENDIF \n");
                 break;
            case FUN: cout<<"fun"<<endl;
                 fprintf(data,"%s proto stdcall  ",x->o2->value.namekey);
                  cout<<"fun"<<x->o2->value.namekey<<endl;
                 FN_1(x->o2);
                 for(int k=count_var;k>0;k--)
                 {
                     if(k==1)
                        fprintf(data,":DWORD\n");
                     else
                        fprintf(data,":DWORD,");
                        cout<<"work"<<endl;
                 }
                 fprintf(code,"%s proc ",x->o2->value.namekey);

                 for(int k=0;k<count_var;k++)
                 {
                     if(k==count_var-1)
                        fprintf(code,"%s:DWORD\n",Naming[k].c_str());
                     else
                        fprintf(code,"%s:DWORD,",Naming[k].c_str() );
                 }
                 c(x->o1);
                 fprintf(code,"\n ret\n%s endp",x->o1->value.namekey);
                 cout<<"WORKEND============="<<endl;
                 break;
            case FUN1:
                 cout<<"fun1"<<endl;
                count_var=0;
                cout<<"FN1===="<<endl;
                 fprintf(code,"\ninvoke %s",x->value.namekey);
               //  FN_Awake(x->o3);
                 fprintf(code,"\n");
                 break;
            case MAINE: cout<<"maine"<<x->value.namekey<<endl;
                fprintf(code,"main Proc\nFINIT\n");
                c(x->o1);
                fprintf(code,"invoke crt__getch\ninvoke ExitProcess,0 \nmain endp\nEND main");
            case GET:
                fprintf(code,"LEA eax,%s\n",x->o1->value.namekey);
                fprintf(code,"PUSH eax");
                fprintf(code,"MOV eax,offset prnt_scan_real\n");
                fprintf(code,"PUSH eax \n");
                fprintf(code,"CALL scanf \n");
                fprintf(code,"ADD esp,8 \n");
            break;
            case PUT:
                fprintf(data,"var_%d DB ",count_str);
                fprintf(data,"%c%s%c,0",34,x->o1->value.namekey,34);
                fprintf(code,"mov eax,offset var_%d\n",count_str);
                fprintf(code,"push eax \n");
                fprintf(code,"call printf \n");
                fprintf(code,"ADD esp,4 \n");
                break;
            case MAS:
                fprintf(data,"%s DD %d dup(0.0)",x->value.namekey,x->o3->value.namekey);
            break;
        }
    }

    void var_1 (node *x)
    {
        if (x->o2->o2!=NULL) var_1(x->o2);
        cout<<"lala"<<x->o1->o1->value.namekey<<endl;
        fprintf(data,"\n%s ",x->o1->o1->value.namekey);
        cout<<"lala1"<<x->o1->o2->value.namekey<<endl;
        if(x->o1->o2->value.codekey==Integersy||x->o1->o2->value.codekey==floatsy)
            fprintf(data,"DD ");
        cout<<"lala2"<<x->o1->o2->value.namekey<<endl;
        fprintf(data,"%s","0\n");
    }
   void var_2 (node *x)
    {

        if (x->o1 != NULL)
        {
            var_2(x->o1);
            var_2(x->o2);
            switch(x->kind)
            {
                case ADD:fprintf(code,"fld dword ptr[esp]\n",x->value.namekey);
                fprintf(code,"pop eax\n\
    fadd dword ptr[esp]\n\
    pop eax\n\
    fstp dword ptr [esp]\n");break;

                case SUB:fprintf(code,"fld dword ptr[esp]\n",x->value.namekey);
                fprintf(code,"pop eax\n\
    fsub dword ptr[esp]\n\
    pop eax\n\
    fstp dword ptr [esp]\n");break;

                case MLT:fprintf(code,"fld dword ptr[esp]\n",x->value.namekey);
                fprintf(code,"pop eax\n\
    fmul dword ptr[esp]\n\
    pop eax\n\
    fstp dword ptr [esp]\n");break;

                case DIV:fprintf(code,"fld dword ptr[esp]\n",x->value.namekey);
                fprintf(code,"pop eax\n\
    fdiv dword ptr[esp]\n\
    pop eax\n\
    fstp dword ptr [esp]\n");break;

            }
        }
        else
            if(x->value.codekey==intc)
            {
                Count_cnst++;
                fprintf(data,"%s%d DD %s.0\n",Name,all,x->value.namekey);
                fprintf(code,"push %s%d\n",Name,all);
                all++;
            }
            else
                fprintf(code,"push %s\n",x->value.namekey);
    }
    void FN_Awake(node *x)
    {
        cout<<"AWAKE "<<x->kind<<endl;

        if(x->kind==VAR)
        {
            fprintf(code,",%s%d",Name,all,x->value.namekey);
        }

        if(x->kind==CST)
        {
            cout<<"NUMBER"<<endl;
            Count_cnst++;
            fprintf(data,"%s%d DD %s.0\n",Name,all,x->value.namekey);
            fprintf(code,",%s%d",Name,all,x->value.namekey);
            all++;
        }
        if(x->o1!=NULL)
            FN_Awake(x->o1);
        if(x->o2!=NULL)
            FN_Awake(x->o2);
    }
    void FN_1(node * x)
    {
        cout<<x->o1->o1->value.namekey<<endl;
        if(x->o1->kind==LET)
        {
            Naming[count_var]=x->o1->o1->value.namekey;
            cout<<"FN1 "<<Naming[count_var]<<endl;
            count_var++;


        }
        //if(x->o1!=NULL) FN_1(x->o1);
        if(x->o2!=NULL)
            FN_1(x->o2);
    }
    void IF_test(node *x)
    {
        fprintf(code,"eax");

        switch(x->value.codekey)
        {
            case later: fprintf(code,"<");break;
            case greater:fprintf(code,">");break;
            case equal:fprintf(code,"==");break;
        }

        fprintf(code,"ebx \n");
    }



};
void print (node *t, int u)
    {
        if (t == NULL) { return;}              //Если дерево пустое, то отображать нечего, выходим
        else //Иначе
        {
            print(t->o1, ++u);                   //С помощью рекурсивного посещаем левое поддерево
            for (int i=0; i<u; ++i) cout<<"\t";
            cout << t->kind<<":"<<t->value.namekey<< endl;            //И показываем элемент
            u--;
        }

        print (t->o2, ++u);
        print (t->o3, ++u);          //С помощью рекурсии посещаем правое поддерево
    }
int main()
{

    lekser lek;
    lek.read();
    lek.~lekser();

    parser par;
    emitter emit; emit.c(par.program());
    //print (par.program(),0);
    ifstream inc("includ.txt");
    ifstream dat("data.txt");
    ifstream cod("code.txt");
    ofstream asem("asem.txt");
    asem<<inc.rdbuf();
    asem<<dat.rdbuf();
    asem<<cod.rdbuf();
    inc.close();
    dat.close();
    cod.close();
    asem.close();
    return 0;
}
