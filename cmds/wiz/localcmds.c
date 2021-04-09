// localcmds.c

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        mixed *cmds;
        object  ob;
        int i;

        if (!arg) ob = me;
        else if (arg == "here") ob = environment(me);
        if (!ob) {
        arg = lower_case(arg);
        ob = find_player(arg);
        }
                if ( !ob ) ob = find_living(arg);
                if ( !ob ) ob = present(arg, environment(me));
                if( !ob ) ob = me;

        cmds = ob->query_commands();
        write(ob->query("name")+"身上及四周的物品与所在的环境提供以下指令：\n");
        for(i = 0; i<sizeof(cmds); i++) {
                if( cmds[i][2]==me ) continue;
                printf("%-15s  %2d %O\n", cmds[i][0], cmds[i][1], cmds[i][2]);
        }
        return 1;
}

int help()
{
        write(@TEXT
指令格式：localcmds

列出你身上及四周的物品与所在的环境提供的所有指令。
TEXT
        );
        return 1;
}


