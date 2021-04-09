// update.c
// Creatied by DIABLO@XYXY

#include <ansi.h>
#include "/doc/help.h"

inherit F_CLEAN_UP;

int update_player(object me);

int main(object me, string file)
{
        int i;
        object obj, *inv;
        string err;
       if(!file) return notify_fail("没有这个档案。\n");
        if (! SECURITY_D->valid_read(file, me, "read"))
                return notify_fail("没有这个档案。\n");

        seteuid( geteuid(me) );

        if (!file) file = me->query("cwf");
        if (!file)
                return notify_fail("你要重新编译什么档案？\n");

        if( (obj = present(file, environment(me))) && interactive(obj) )
                return update_player(obj);

        if( file == "me" )
                return update_player(me);
        else {
                file = resolve_path(me->query("cwd"), file);
                if( !sscanf(file, "%*s.c") ) file += ".c"; 
        }

        if( file_size(file) < 0 )
                return notify_fail("没有这个档案。\n");

        if (!SECURITY_D->valid_write(file,me,"update"))
            return notify_fail("读写权限不够无法更新！\n");

        me->set("cwf", file);

        if (obj = find_object(file)) {
                if( file_name(obj)==VOID_OB )
                        return notify_fail("你不能在 VOID_OB 里重新编译 VOID_OB。\n");
                inv = all_inventory(obj);
                i = sizeof(inv);
                while(i--)
                        if( userp(inv[i]) ) inv[i]->move(VOID_OB, 1);
                        else inv[i] = 0;
                destruct(obj);
        }

        if (obj) return notify_fail("无法清除旧程式码。\n");

        write("重新编译 " + file + " ...");
        err = catch( call_other(file, "???") );
        if (err)
                printf( "发生错误：\n%s\n", err );
        else {
                write("成功！\n");
        MONITOR_D->report_system_object_msg(me,HIR"正在重新编译"+"("+file+")!"NOR);
                if( (i=sizeof(inv)) && (obj = find_object(file))) {
                        while(i--)
                                if( inv[i] && userp(inv[i]) ) inv[i]->move(obj, 1);
                }
        }

        return 1;
}

private int update_player(object me)
{
        object env, link_ob, obj;
        object *ob, *dob;
        mapping equip;
        int i;

        if (wiz_level(me) > wiz_level(this_player()))
                return notify_fail("你没有权限更新这个人物。\n");

        seteuid(getuid());
        env = environment(me);

        // First, create the new body.
        link_ob = me->query_temp("link_ob");
        if (! link_ob)
        {
                link_ob = new(LOGIN_OB);
                link_ob->set("id", me->query("id"));
                if (! link_ob->restore())
                {
                        return 1;
                }
                if (interactive(me))
                        link_ob->set_temp("ip_number", query_ip_number(me));
        }

        if (link_ob->query("id") != getuid(me))
        {
                write (sprintf("连接对象的ID(%s)和用户的ID(%s)不相同，不能"
                       "更新该玩家。\n", link_ob->query("id"), getuid(me)));
                return 1;
        }

        MONITOR_D->report_system_object_msg(this_player(),HIR"正在更新玩家"+"("+(string)me->query("name")+")!"NOR);

        obj = LOGIN_D->make_body(link_ob);
        if (! obj) return 0;

        // Save the data and exec the player to his/her link object.
        ob = all_inventory(me);
        equip = ([ ]);
        for (i = 0; i < sizeof(ob); i++)
                equip += ([ ob[i] : ob[i]->query("equipped") ]);
        ob->move(VOID_OB);

        // 保存用户的进度
        me->save();

        // 如果在线，移动互动对象
        if (interactive(me))
                exec(link_ob, me);
        destruct(me);

        // Restore new body and exec to it via enter_world in LOGIN_D
        obj->restore();
        LOGIN_D->enter_world(link_ob, obj, 1);
        dob = all_inventory(obj);
        for (i = 0; i < sizeof(dob); i++)
                destruct(dob[i]);

        write("身体更新完毕。\n\n");
        obj->move(env);
        ob->move(obj);

        if (! interactive(obj))
                destruct(link_ob);

        for (i = 0; i < sizeof(ob); i++)
        {
                if (equip[ob[i]] == "worn")
                        ob[i]->wear();
                if (equip[ob[i]] == "wielded")
                        ob[i]->wield();
        }
        obj->write_prompt();

        return 1;
}

int help(object me)
{
  write(@HELP
指令格式 : update <档名|here|me|玩家名>
 
这个指令可以更新档案, 并将新档的内容载入记忆体内. 若目标为
'here' 则更新所在环境. 若目标为 'me' 则更新自己的人物. 若目
标为玩家则可更新玩家物件.
 
HELP
    );
    return 1;
}


