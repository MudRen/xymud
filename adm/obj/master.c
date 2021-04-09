#include <localtime.h>
#include <ansi.h>

#define	INSTALL_CRASH_SAVE	1

object connect(int port)
{
        object login_ob;
        mixed err;
        if (port == 5555)
        {
                set_encoding("GBK");
        }
        err = catch (login_ob = new (LOGIN_OB));

        if (err)
        {
                write("现在有人正在修改使用者连线部份的程式，请待会再来。\n");
                write(err);
                destruct(this_object());
        }
        return login_ob;
}
mixed compile_object(string file)
{
        object daemon;

        if( daemon = find_object(VIRTUAL_D) )
                return daemon->compile_object(file);
        else
                return 0;
}
protected void crash(string error, object command_giver, object current_object)
{
#if INSTALL_CRASH_SAVE
        object ob;
        string dump_dir;
        string user;
        string flogin, fuser;
        mixed lt;
#endif

         mixed cmds;
  int i;

  efun::shout("系统核心发出一声惨叫：哇—哩—咧—\n");
  efun::shout("系统核心告诉你：要当机了，自己保重吧！\n");
  log_file("static/crash", MUD_NAME + " crashed on: " + ctime(time()) +
           ", error: " + error + "\n");
  if (command_giver)
  {
    log_file("static/crash",
        sprintf( "this_player: %O %s\n",command_giver, geteuid(command_giver)));
    write_file("/log/static/lastcrash",
        sprintf( "this_player: %O %s\n",command_giver, geteuid(command_giver)));
    cmds = command_giver->query_commands();
    for (i = 0; i < sizeof(cmds); i++)
    {
      if (cmds[i][2] == command_giver)
        continue;
      log_file("static/crash", sprintf("%-15s  %2d %O\n", cmds[i][0], cmds[i][1], cmds[i][2]));
    }
    if (environment(command_giver))
      log_file("static/crash", sprintf("in where: %s(%s)。\n",
                             environment(command_giver)->query("short"),
                             base_name(environment(command_giver))));
      log_file("static/crash", sprintf( "this_player: %O 。 end command (%s)\n",
                             command_giver,
                             command_giver->query_last_input()));
  }

  if (current_object)
  {
    log_file("static/crash", sprintf("this_object: %O\n", current_object));
  }

#if INSTALL_CRASH_SAVE
        lt = localtime(time());
        lt[LT_MON]++;
        dump_dir = sprintf(DUMP_DIR "%d-%d-%d/", lt[LT_YEAR], lt[LT_MON], lt[LT_MDAY]);
        foreach (ob in users())
        {
                reset_eval_cost();

                // backup user data to dump
                user = geteuid(ob);
                if (! stringp(user))
                        continue;
                flogin = "login/" + user[0..0] + "/" + user + __SAVE_EXTENSION__;
                fuser  = "user/"  + user[0..0] + "/" + user + __SAVE_EXTENSION__;
                if (file_size(DATA_DIR + flogin) > 0 &&
                    file_size(DATA_DIR + fuser) > 0)
                {
                        // exist in data, I will backup it to dump
                        assure_file(dump_dir + flogin);
                        assure_file(dump_dir + fuser);
                        cp(DATA_DIR + flogin, dump_dir + flogin);
                        cp(DATA_DIR + fuser,  dump_dir + fuser);
                        log_file("static/dump",
                                 sprintf("backup user(%s) to dump\n", user));
                }
                ob->save();
        }
#endif
}
protected string *update_file(string file)
{
        string *list;
        string str;
        int i;

        str = read_file(file);
        if (!str)
                return ({});
        list = explode(str, "\n");
        for (i = 0; i < sizeof(list); i++) {
                if (list[i][0] == '#') {
                        list[i] = 0;
                }
        }
        return list;
}
string *epilog(int load_empty)
{
        string *items;

        items = update_file(CONFIG_DIR + "preload");
        return items;
}
void preload(string file)
{
        int t1;
        string err;

        if (file_size(file + ".c") == -1)
                return;

        t1 = time();
        write("Preloading : " + file );
        err = catch(call_other(file, "??"));
        if (err)
                write(" -> Error " + err + " when loading " + file + "\n");
        else
                write(".... Done.\n");

}
void log_error(string file, string message)
{
        string name, home;

        if (find_object(SIMUL_EFUN_OB))
                name = file_owner(file);

        if (name)
                home = user_path(name);
        else
                home = LOG_DIR;

        if (strsrch(message, "Warning") == -1)
        {
                if (this_player(1))
                {
                        if (wizardp(this_player(1)))
                                efun::write("编译时段错误：" + message + "\n");
                        else
                                efun::write(get_config(11) + "\n");
                }
                // 记录错误日志
                efun::write_file(home + "log_error", message);
        }
        else
        {
                // 记录警告日志
                efun::write_file(home + "log", message, 1);
        }
}
int save_ed_setup(object who, int code)
{
        string file;

    if (!intp(code))
        return 0;
    file = user_path(getuid(who)) + ".edrc";
    rm(file);
    return write_file(file, code + "");
}
int retrieve_ed_setup(object who)
{
   string file;
   int code;

    file = user_path(getuid(who)) + ".edrc";
    if (file_size(file) <= 0) {
        return 0;
    }
    sscanf(read_file(file), "%d", code);
    return code;
}
void destruct_env_of(object ob)
{
        if (!interactive(ob))
                return;
        tell_object(ob, "你所存在的空间被毁灭了。\n");
        ob->move(VOID_OB);
}
string make_path_absolute(string file)
{
        file = resolve_path((string)this_player()->query("cwd"), file);
        return file;
}
string get_save_file_name(string fname)
{
    return fname + "." + time();
}

string get_root_uid()
{
   return ROOT_UID;
}

string get_bb_uid()
{
   return BACKBONE_UID;
}

string creator_file(string str)
{
        return (string)call_other(SIMUL_EFUN_OB, "creator_file", str);
}

string domain_file(string str)
{
        return (string)call_other(SIMUL_EFUN_OB, "domain_file", str);
}

string standard_trace(mapping error, int caught)
{
        int i, s;
        string res;
        object me;
        mixed *cmds;

        /* keep track of number of errors per object...if you're into that */

        res = (caught) ? "错误讯息被拦截：" : "";

        res = sprintf("\n[执行时段错误]: %s[程式] %s%s:%i\n[物件]: %O\n",               error["error"],         error["file"],          error["file"]==error["program"] ? "" : "(" + error["program"] + ")",           error["line"],          error["object"]);

        if (! error["object"] && (me = this_player()))
        {
                res += sprintf("当前玩家：%s(%s) - %O  所在环境：%O\n",
                               me->name(1), me->query("id"), me, environment(me));
                cmds = me->query_commands();
                res += me->name(1) + "身上及四周的物品与所在的环境提供以下指令：\n";
                for(i = 0; i<sizeof(cmds); i++)
                        res += sprintf("%-15s  %2d %O\n",
                                       cmds[i][0], cmds[i][1], cmds[i][2]);

                res += sprintf("当前的命令：%O\n", me->query_last_input());
        }

        i = 0;
        s = sizeof(error["trace"]);
        res += "[回溯]:\n";
	for (i=0; i < s; i++) {
		res = sprintf("%s%-25s %s%s  %i 行，物件： %O\n",
			res,
			error["trace"][i]["function"] + "()",
			error["trace"][i]["file"],
	        error["trace"][i]["file"]==error["trace"][i]["program"] ?
	        	"" : "(" + error["trace"][i]["program"] + ")",
			error["trace"][i]["line"],
			error["trace"][i]["object"]
		);
	}
	res += "\n";
        return res;
}
string author_file(string str)
{
        return (string)call_other(SIMUL_EFUN_OB, "author_file", str);
}
string error_handler( mapping error, int caught )
{
    if (this_player(1)) {
        this_player(1)->set_temp("error", error);
        tell_object(this_player(1), standard_trace(error, caught));
    }
    return standard_trace(error, caught);
}

// valid_shadow: controls whether an object may be shadowed or not
int valid_shadow( object ob ) { return 0; }

// valid_override: controls which simul_efuns may be overridden with
//   efun:: prefix and which may not.  This function is only called at
//   object compile-time

int valid_override( string file, string name )
{
        // simul_efun can override any simul_efun by Annihilator
        if (file == SIMUL_EFUN_OB || file==MASTER_OB)
                return 1;

        // Must use the move() defined in F_MOVE.
        if ((name == "move_object") && file != F_MOVE && file != F_COMMAND)
                return 0;

        if ((name == "destruct") && ! sscanf(file, "/adm/simul_efun/%s", file))
                return 0;

    //  may also wish to protect destruct, shutdown, snoop, and exec.
        return 1;
}
// valid_seteuid: determines whether an object ob can become euid str
int valid_seteuid( object ob, string str )
{
    return (int)SECURITY_D->valid_seteuid( ob, str );
}

// valid_socket: controls access to socket efunctions
int valid_socket( object eff_user, string fun, mixed *info )
{
        return 1;
}

// valid_asm: controls whether or not an LPC->C compiled object can use
//   asm { }
int valid_asm( string file )
{
    return 1;
}

// valid_compile_to_c: controls whether or not an object may be compiled
//   via LPC->C
int valid_compile_to_c( string file )
{
    return 1;
}

// valid_hide: controls the use of the set_hide() efun, to hide objects or
//   see hidden objects
int valid_hide( object who )
{
    return 1;
}

// valid_object: controls whether an object loaded by the driver should
//   exist
int valid_object( object ob )
{
    return (!clonep(ob)) || inherits(F_MOVE, ob);
}

// valid_link: controls use of the link() efun for creating hard links
//   between paths
int valid_link( string original, string reference )
{
    return 0;
}

// valid_save_binary: controls whether an object can save a binary
//   image of itself to the specified "save binaries directory"
//   (see config file)
int valid_save_binary( string filename )
{
    return 1;
}

// valid_write: write privileges; called with the file name, the object
//   initiating the call, and the function by which they called it.

int valid_write( string file, mixed user, string func )
{
        object ob;

        if( ob = find_object(SECURITY_D) )
                return (int)SECURITY_D->valid_write(file, user, func);

        return 0;
}

// valid_read: read privileges; called exactly the same as valid_write()
int valid_read( string file, mixed user, string func )
{
        return 1;
}

string object_name(object ob)
{
        if( ob ) return ob->name();
}

void create()
{
        write("master: loaded successfully.\n");
}

int valid_bind(object binder, object old_owner, object new_owner)
{
//        if( userp(new_owner) ) return 0;
//        if( geteuid(binder)==ROOT_UID ) return 1;
//        if( clonep(new_owner) ) return 1;
        return 1;
}
