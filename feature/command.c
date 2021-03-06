// #pragma optimize

#include <ansi.h>
#include <command.h>
#include <dbase.h>
#include <origin.h>

// Let command path be static, thus we can make sure no one can get command
// path directly from restore_object().
nosave string *path;

// Leave this to allow other objects can search your commands such as
// help, which...
string find_command(string verb)
{
        object me=this_object();

        //added by mon 11/23/97
        if(userp(me)&& (me->query_temp("d_mana"))>0) {
                if(me->query_temp("is_living")!=1) {
                        if(verb!="bian" && verb!="chat" && verb!="say"
                        && verb!="tell" && verb!="reply" && verb!="look")
                                return (string)notify_fail("别忘了你现在是一"+
                                        (undefinedp(me->query_temp("unit"))?
                                        "个":me->query_temp("unit"))
                                        +me->name()+"！\n");
                }
        }

        return (string)COMMAND_D->find_command(verb, path);
}

// This is the add_action hook handling movement, commands, emotes and
// channels. Optimization is needed.
// private nomask int command_hook(string arg)
nomask int command_hook(string arg)
{
        string verb, file;
        verb = query_verb();

	if( !wizardp(this_object()) && !this_object()->query("env/immortal") )
	{
		if( this_object()->is_blind() )
			return notify_fail(this_object()->query_blind_msg()+"\n");
		if( this_object()->is_hunluan() )
		{
			arg = COMMAND_D->random_command(0,path);
			verb = arg;
		}
	}
        if( arg && userp(this_object()) && !wizardp(this_object()) )
        	arg=replace_string(arg,ESC,"");
        if( !arg
        &&   (environment() && stringp( environment()->query("exits/" + verb) ) )
        &&   stringp(file = find_command("go"))
        &&   call_other(file, "main", this_object(), verb))
                ;

        else if( stringp(file = find_command(verb))
        &&  call_other(file, "main", this_object(), arg))
                ;

        else if( EMOTE_D->do_emote( this_object(), verb, arg ) )
                ;

        else if( CHANNEL_D->do_channel( this_object(), verb, arg ) )
                ;

        else return 0;
        return 1;
}

// private nomask void set_path(string *p)
nomask void set_path(string *p)
{
        path = p;
}

string *query_path() { return path; }
mixed *query_commands() { return commands(); }

int force_me(string cmd)
{
        if( geteuid(previous_object()) != ROOT_UID )
                return 0;
        return command( this_object()->process_input(cmd) );
}

nosave int enabled = 0;

nomask void enable_player()
{
        if( stringp(query("id")) )
        	set_living_name(query("id"));
        else	set_living_name(query("name"));

        delete_temp("disabled");
        if (! enabled) {
                enabled = 1;
                enable_commands();
                add_action("command_hook", "", 1);
        }

        if( !userp(this_object()) )
                set_path(NPC_PATH);
        else
                switch( wizhood(this_object()) ) {
                        case "(admin)":
                                set_path(ADM_PATH);
                                enable_wizard();
                                break;
                        case "(arch)":
                                set_path(ARC_PATH);
                                enable_wizard();
                                break;
                        case "(wizard)":
                                set_path(WIZ_PATH);
                                enable_wizard();
                                break;
                        case "(apprentice)":
                                set_path(APR_PATH);
                                enable_wizard();
                                break;
                        case "(immortal)":
                                set_path(IMM_PATH);
                                enable_wizard();
                                break;
                        case "(elder)":
                                set_path(ELD_PATH);
                                enable_wizard();
                                break;
/*                        case "(boss)":
                                set_path(BOSS_PATH);
                                enable_wizard();
                                break;
 */
                       default:
                                set_path(PLR_PATH);
                }
}

nomask void disable_player(string type)
{
        if( geteuid(previous_object())!=ROOT_UID
        &&   previous_object()!=this_object()) return;

        set("disable_type", type);
        set_temp("disabled", 1);
        if (enabled) {
                enabled = 0;
                disable_commands();
                enable_commands();  // enable command again so this object would be
                            // marked living again. block command in alias.c
                            // instead of here.

        }
}
