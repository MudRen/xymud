// message.c
#include <ansi.h>

// change to english sigh to chinese
//!();:'"?.,
//！（）；：‘“”“”？。，
string _chinese_desc(string arg)
{
	if( !arg )
		return "";
        arg = replace_string(arg, ",", "，");
        arg = replace_string(arg, "!", "！");
        arg = replace_string(arg, "(", "（");
        arg = replace_string(arg, ")", "）");
        arg = replace_string(arg, ";", "；");
        arg = replace_string(arg, ":", "：");
        arg = replace_string(arg, "'", "‘");
        arg = replace_string(arg, "?", "？");
        arg = replace_string(arg, "......", "……");
        arg = replace_string(arg, "....", "……");
        arg = replace_string(arg, ".", "。");
        return arg;
}

// sort a chinese string (must be chinese), align the
// string with then len. the prefix is used when the desc
// will be lead by another string or space with length is prefix.
varargs string sort_string(string input, int width, int prefix)
{
    int i;
    int sl;  // 字符串长度
    int len; // 字符串宽度
    int esc;
    string result;

    result = "";
    esc = 0;
    if (!width) width = 78;
    len = prefix;
    sl = strlen(input);
    for (i = 0; i < sl; i++)
    {
        if (len >= width && input[i] != '\n')
        {
            int k = i;
            // ANSI颜色字符处理
            if (input[i] == 27)
                while (k < sl && input[k++] != 'm')
                    ;

            switch ((k < sl) ? input[k..k] : 0)
            {
            // 部分中英文符号不换行
            case "’":   //8217
            case "”":   //8221
            case "、":  //12289
            case "。":  //12290
            case "！":  //65281
            case "）":  //65289
            case "，":  //65292
            case "：":  //65306
            case "；":  //65307
            case "？":  //65311
            case " ":   //32
            case "!":   //33
            case "”":   //34
            case "'":   //34
            case ")":   //41
            case ",":   //44
            case ".":   //46
            case ":":   //58
            case ";":   //59
            case "?":   //63
                if (k != i)
                {
                    result += input[i..k];
                    i = k;
                    continue;
                }
                break;
            default:
                len = 0;
                result += "\n";
                break;
            }
        }

        if (input[i] == 27)
            esc = 1;

        if (!esc)
        {
            // 非英文字符
            if (input[i] > 160)
            {
                result += input[i..i];
                len += 2;
                continue;
            }
            // 换行
            if (input[i] == '\n')
            {
                result += "\n";
                len = 0;
                continue;
            }
            len++;
        }
        if (esc && input[i] == 'm')
            esc = 0;

        result += input[i..i];
    }

    if (len)
        result += "\n";

    return result;
}

string sort_msg(string input)
{
        return sort_string(input,64,0);
}

varargs void message_vision(string msg, object me, object you,int no_sort)
{
	string my_gender, your_gender, my_name, your_name;
	string str1, str2, str3;

	if(!me) return;

	my_name= me->name();
	my_gender = me->query("gender");

	if(!my_name || !my_gender) return; //mon 10/23/97

	str1 = replace_string(msg,  "$P", gender_self(my_gender));
	str1 = replace_string(str1, "$N", gender_self(my_gender));
	str3 = replace_string(msg,  "$P", my_name);
	str3 = replace_string(str3, "$N", my_name);
	str3 = replace_string(str3, "$S", RANK_D->query_self(me));
	str3 = replace_string(str3, "$s", RANK_D->query_self_rude(me));
	str3 = replace_string(str3, "$C", RANK_D->query_respect(me));
        str3 = replace_string(str3, "$c", RANK_D->query_rude(me));
	if( you ) {
		your_name= you->name();
		your_gender= you->query("gender");
		str2 = replace_string(msg,  "$P", gender_pronoun(my_gender));
		str2 = replace_string(str2, "$p", gender_self(your_gender));
		str2 = replace_string(str2, "$N", my_name);
		str2 = replace_string(str2, "$n", gender_self(your_gender));
		str2 = replace_string(str2, "$R", RANK_D->query_respect(you));
        	str2 = replace_string(str2, "$r", RANK_D->query_rude(you));

		if( !no_sort )
			str2 = sort_string(str2,76,0);
		message("vision", str2, you);
		str1 = replace_string(str1, "$p", gender_pronoun(your_gender));
		str1 = replace_string(str1, "$n", your_name);
		str3 = replace_string(str3, "$p", your_name);
		str3 = replace_string(str3, "$n", your_name);
	}
	if( !no_sort )
		str1 = sort_string(str1,76,0);
	message("vision", str1, me);
	if( !no_sort )
		str3 = sort_string(str3,76,0);
	if(environment(me)) { //mon 10/23/97
	  	if(you)
		    message("vision", str3,  environment(me), ({ me, you}) );
		else
		    message("vision", str3,  environment(me), ({ me}));
	  	// broadcasting to remote rooms, snowcat feb 8 1998
	  	if(environment(me)->query("broadcast"))
	  		environment(me)->broadcast(str3);
	}
}

object *all_interactive()
{
        return efun::users();
}

void message_system(string message)
{
	message("system", HIW "\n【系统提示】" + message + "\n" NOR,all_interactive(), 0);
}

void tell_object(object ob, string str)
{
	if(ob)
	{
		str = sort_string(str,76,0);
		message("tell_object", str, ob);
	}
}

varargs void tell_room(mixed ob, string str, object *exclude)
{
	if( ob)
	{
		str = sort_string(str,76,0);
		message("tell_room", str, ob, exclude);
	  	// broadcasting to remote rooms, snowcat feb 8 1998
	  	if(ob->query("broadcast"))
	  		ob->broadcast(str);
	}
}

void shout(string str)
{
	message("shout", str, users(), this_player());
}

void write(string str)
{
	if( this_player() )
		message("write", str, this_player());
	else if( previous_object() )
		message("write", str, previous_object());
	else	efun::write(str);
}

varargs void say(string str, mixed exclude)
{
	object ob = 0;
	if( living(previous_object()) )
		ob = previous_object();
	else if( this_player() )
		ob = this_player();
	if( ob && environment(ob))
	{
		str = sort_string(str,76,0);
		message("say", str, environment(ob), ob);
  		// broadcasting to remote rooms, snowcat feb 8 1998
  		if(environment(ob)->query("broadcast"))
  			environment(ob)->broadcast(str);
  	}
}

varargs void printf (string msg, mixed a1, mixed a2, mixed a3, mixed a4,
	 mixed a5, mixed a6, mixed a7, mixed a8, mixed a9, mixed a10,
	 mixed a11, mixed a12, mixed a13, mixed a14, mixed a15, mixed a16)
{
	msg = sprintf (msg,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16);
    	write (msg);
}

int notify_fail (mixed arg)
{
	if( arg && stringp(arg) )
		arg = sort_string(arg,76,0);
    	return efun::notify_fail (arg);
}

int err_msg(string arg)
{
	write(arg);
	return 1;
}

#define SHOW_ALL                0
#define SHOW_DAMAGE             1
#define SHOW_NONE               2
nomask varargs void message_combatd(string msg, object me, object you)
{
	if( COMBAT_D->query_message_type(me,you)<2 )
		message_vision(msg,me,you);
}

// Modified By Jingxue 2007/06/16
// 把两段文字纵向相加 wi参数为左边文字的宽度
// 当左边比右边窄时 用空格代替
varargs string mix_str( string msg_one, string msg_two, int wi )
{
	string msg;
	string *field_one, *field_two;
	int max_line, i;

	if (msg_one == "")
		return msg_two;
	else
		field_one = explode(msg_one, "\n");
	if (msg_two == "")
		return msg_one;
	else
		field_two = explode(msg_two, "\n");
	max_line = (sizeof(field_one) > sizeof(field_two))?sizeof(field_one):sizeof(field_two);
	msg = "";

	for (i=0;i<max_line;i++)
	{
		if ( i < sizeof(field_one) )
			msg += field_one[i];
		if ( i < sizeof(field_two) )
		{
			if ( wi > 0 && i >= sizeof(field_one) )
				msg += repeat_string(" ", wi);
			msg += field_two[i];
		}
		msg += "\n";
	}
	return msg;
}
