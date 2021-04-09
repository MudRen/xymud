// more.c

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        string file;
        object ob;
        int otp_c;

        seteuid(geteuid(me));
        if (! arg) return notify_fail("指令格式 : more <档名>|<物件名> -c\n");
        if (sscanf(arg, "%s -c", arg))
        {
                otp_c = 1;
        }
        else    otp_c = 0;
        file = resolve_path(me->query("cwd"), arg);
        if (file_size(file) < 0)
        {
                ob = present(arg, me);
                if (! ob) ob = present(arg, environment(me));
                if (! ob) return notify_fail("没有这个档案。\n");
                file = base_name(ob) + ".c";
        }

        if (! SECURITY_D->valid_read(file, me, "read"))
                return notify_fail("没有这个档案。\n");

        if (otp_c)
        {
                me->start_more(color_filter(read_file(file)));
                return 1;
        }
        me->start_more_file(file);
        return 1;
}

int help(object me)
{
        write(@HELP
指令格式 : more <档案名> -c

这个指令让你可以以分页方式查阅一个文件的内容。
使用-c参数则以color方式浏览文件，多用于浏览
welcome或者是help文件.

see also: cat
HELP );
        return 1;
}

