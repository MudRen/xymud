#include <ansi.h>
inherit ITEM;

void create()
{
        set_name("问题卷",({"quest"}));
        set_weight(1);
        set("env/invisibility",99);
        setup();
}

void init()
{
        string str;
        if( userp(this_player()) && this_player()==query("owner") )
        {
                str = ("/adm/daemons/coded.c")->code_math(this_player());
                this_player()->set_temp("Code_quest",str);
                add_action("do_cmds","",1);
                add_action("do_answer","answer");
        }
}

int do_cmds()
{
        string str,verb = query_verb();
        if( str=this_player()->query_temp("Code_quest") )
        {
                if( verb!="answer" )
                {
                        tell_object(this_player(),"请回答下面的问题:\n");
                        tell_object(this_player(),str);
                        tell_object(this_player(),"请回答(answer)出你的答案:\n");
                        return 1;
                }
        }
        return 0;
}

int do_answer(string arg)
{
        string ff,r;
        object me = this_player();
        if( !arg )
                return 0;
        if( !me->query_temp("Code_quest") )
                return 0;
        r = query("exit");
        if( !r )
                r = "/d/dntg/sky/tgqs"+sprintf("%d",1+random(8));               
        ff = me->query_temp("Code_answer")+"";
        arg = arg+"";
        me->delete_temp("Code_quest");
        me->delete_temp("Code_answer");
        if( ff!=arg )
        {
                tell_object(me,HIR"很抱歉，你答错了！\n"NOR);
                me->move(r,2);
        } 
        else    tell_object(me,HIR"恭喜你！答对了。\n"NOR);
        destruct(this_object());
        return 1;
}
