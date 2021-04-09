/******************************************/
/* MUDLIB：Glory of Days Past 〓光辉岁月〓 */
/* Updated Admin By Waiwai@2003/04/09     */
/* Admin Email：wkzstory@21cn.com         */
/******************************************/
// edit.c Yuj@SJ 20000212
// Update by waiwai@2003/08/31

#include <ansi.h>

int edit(function callback)
{
    write(HIG"\n系统提示：完成时用 "BLINK HIY"."NOR HIG" 确定。放弃输入用 "BLINK HIR"q\n"NOR);
    write(HIK"每行允许字符数：104 个英文或 52 个汉字以内。\n允许总输入行数：100行，允许总输入字数：5000个中文字符。\n"NOR);

    write(repeat_string("—", 39) + "\n1: ");
    input_to("input_line", "", callback, 1);
    return 1;
}

void input_line(string line, string text, function callback, int ln)
{
    if( line=="." )
    {
//        if (this_object()->query_temp("big5")) text = CONVERT_D->b5_gb(text);
        (*callback)(text);
        return;
    }
    if( line=="q" ) {
        write("输入取消。\n");
        return;
    }
    if (strlen(line) > 104) write(HIG + "请将每行文字控制在 104 个英文或 52 个汉字以内。\n" NOR);
    else {
        text += line + "\n";
        ln++;
    }

    if (strlen(text) > 10000 || ln > 100)
    {
        write(HIG"\n行数超过了100行或字数超过了5000个中文字，系统自动终止，未写完的请另外再写。\n" NOR);
//        if (this_object()->query_temp("big5")) text = CONVERT_D->b5_gb(text+"(未完待续)......\n");
//	else 
	text = text+"\n(未完待续)......\n";

        (*callback)(text);
        return;
    }

//    if (strlen(text) > 10000 || ln > 100) write(HIG + "请长话短说或者另外续写。\n" NOR);

    write(CSI"5D" + ln + ": ");
    input_to((: input_line :), text, callback, ln);
}
