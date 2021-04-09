// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */
 
// emoted.c
// modified by none on 96/10/04
// modified by tool on 96/10/05
// modified by mon@xyj on 10/97 to add support for 
//          intermud emote.

// Modify by Jingxue for XYCQ 6.10.2003

#include <ansi.h>
#include "/cmds/std/block_tell.h"  //mon 9/15/97
                                   //prevent flooding by emote.

inherit F_SAVE;

mapping emote;

//   The emote mapping contains the data base of emote definitions. Each emote
//   is defined in a sub-mapping with the following structure:
//
//   myself   - the message emoter will see
//   target   - the message the target will see when targeted
//   others   - the message others will see when no argument.
//
//   The emote mapping is indexed with the emote 'pattern' instead of emote
//   verb. For example, typing "smile" without argument will cause the daemon
//   search the emote mapping with "smile" as key, and typing "smile someone"
//   will cause the daemon search the emote mapping with "smile $" pattern as
//   the key, while $ means one argument.
//
//   In the message string, the following substitutions will be applied before
//   sending the messages:
//
//   $N     - name of emoter
//   $n     - name of target
//   $P     - pronoun of emoter
//   $p     - pronoun of target
//
//   Original by Annihilator@ESII (11/09/94)
//      $C              - respect call of emoter
//      $c              - rude call of emoter 
//      $R              - respect calling of target
//      $r              - rude calling of target
//      $S              - self calling of emoter
//      $s              - self-rude calling of emoter
//      added by none on 96/10/04 

void create()
{
   	if( !restore() && !mapp(emote) )
     	emote = ([]);
}

int remove()
{
   	save();
   	return 1;
}

string query_save_file() { return DATA_DIR + "emoted"; }

 string color_all_name(object obj)
{
        string *tmp,color;
        color = obj->query("name_color");
        if( !color || !stringp(color) )
                color = "";
        else    color = COLOR_D->replace_color(color,1);
        color = replace_string(color,NOR"","");

        return color;
}
// command_hook() of F_COMMAND call this as an alternate command processor.
// CHANNEL_D also calls this to get emote message.
varargs mixed do_emote(object me, string verb, string arg, string color, int channel_emote, int rumor_emote, int intermud)
{
   	string my_color, target_color, msg_color, str, my_gender, target_gender, msg_postfix;
   	object target;
   	string if_execute;
   	string user_emote;

   	if( !environment(me) ) return 0;

//   if( !mapp(emote) || undefinedp(emote[verb]) ) return 0;
   	if( !mapp(emote) ) return 0;
   	if(undefinedp(emote[verb])) 
   	{
     		if(!channel_emote)  return 0;
     		if(verb[0] < 0x80)  return 0;
     		if(rumor_emote)
        		user_emote = "某人" + verb + "\n";
                else 
                {
                	if(!channel_emote || ! intermud)
        			user_emote = me->name() + verb + "\n";
                	else	user_emote = "$N" + verb + "\n";
                }
       		return user_emote;
   	}

   // Determine the pattern to be searched and the target.
     	if( color ) msg_color=color; 
        else msg_color=NOR CYN; 

   	if( stringp(arg) && arg != "" ) 
   	{
     		target = present(arg, environment(me));

     		if(!objectp(target)) 
     		{
        		if(!channel_emote) return 0;
        		target = find_player(arg);
        		if( !objectp(target) ) return 0;
     		}
     
     		if( !target->is_character() || !me->visible(target) )
        		return notify_fail("你要对谁做这个动作？\n"); 

     		target_gender = target->query("gender");
     		target_color = color_all_name(target);
	     	
     		if( target==me ) 
     		{
        		msg_postfix = "_self";
        		target = 0;
     		} 
     		else	msg_postfix = "_target";
   	} 
   	else	msg_postfix = "";

//mon 9/15/97. for emote flooding.
        if(!channel_emote) 
        {
          	if(!block_tell(me)&&userp(me)) return 1;
   	}

   	my_gender = me->query("gender");
     	my_color = color_all_name(me);

   	if_execute = "";
   	if( stringp(str = emote[verb]["myself" + msg_postfix]) ) 
   	{
     		if_execute = " ";
     		if(rumor_emote)
        		str = replace_string(str, "$N", "某人");
        	else	str = replace_string(str, "$N", my_color+me->name()+msg_color);
     		str = replace_string(str, "$P", gender_self(my_gender)+msg_color);
                str = replace_string(str, "$S", RANK_D->query_self(me)+msg_color);
                str = replace_string(str, "$s", RANK_D->query_self_rude(me)+msg_color);
     		if( objectp(target) ) 
     		{
                	str = replace_string(str, "$C", RANK_D->query_respect(me)+msg_color);
                	str = replace_string(str, "$c", RANK_D->query_rude(me)+msg_color);
	                str = replace_string(str, "$R", RANK_D->query_respect(target)+msg_color);
        	        str = replace_string(str, "$r", RANK_D->query_rude(target)+msg_color);
        		str = replace_string(str, "$n", target_color+target->name()+msg_color);
	        	str = replace_string(str, "$p", gender_pronoun(target_gender)+msg_color);
     		}
     		if( !channel_emote ) message("emote", CYN + str + NOR, me);
   	}
  
   	if( objectp(target) && stringp(str = emote[verb]["target"]) ) 
   	{
     		if_execute = " ";
	     	if(rumor_emote)
        		str = replace_string(str, "$N", "某人"+msg_color);
        	else	str = replace_string(str, "$N", my_color+me->name()+msg_color);
	     	str = replace_string(str, "$P", gender_pronoun(my_gender)+msg_color);
                str = replace_string(str, "$S", RANK_D->query_self(me)+msg_color);
                str = replace_string(str, "$s", RANK_D->query_self_rude(me)+msg_color);
                str = replace_string(str, "$C", RANK_D->query_respect(me)+msg_color);
                str = replace_string(str, "$c", RANK_D->query_rude(me)+msg_color);
                str = replace_string(str, "$R", RANK_D->query_respect(target)+msg_color);
                str = replace_string(str, "$r", RANK_D->query_rude(target)+msg_color);
     		str = replace_string(str, "$n", target_color+target->name()+msg_color);
     		str = replace_string(str, "$p", gender_self(target_gender)+msg_color);

     		if( !channel_emote ) message("emote", CYN + str + NOR, target);
   	}

   	if( stringp(str = emote[verb]["others"+msg_postfix]) ) 
   	{
     		if_execute = " ";
     		if(rumor_emote)
        		str = replace_string(str, "$N", "某人");
        	else if(!channel_emote || !intermud)
        		str = replace_string(str, "$N", my_color+me->name()+msg_color);
     		str = replace_string(str, "$P", gender_pronoun(my_gender)+msg_color);
                str = replace_string(str, "$S", RANK_D->query_self(me)+msg_color);
                str = replace_string(str, "$s", RANK_D->query_self_rude(me)+msg_color);
     		if( objectp(target) ) 
     		{
                        str = replace_string(str, "$C", RANK_D->query_respect(me)+msg_color);
                        str = replace_string(str, "$c", RANK_D->query_rude(me)+msg_color);
                        str = replace_string(str, "$R", RANK_D->query_respect(target)+msg_color);
                        str = replace_string(str, "$r", RANK_D->query_rude(target)+msg_color);
        		str = replace_string(str, "$n", target_color+target->name()+msg_color);
        		str = replace_string(str, "$p", gender_pronoun(target_gender)+msg_color);
     		}
     		if( !channel_emote ) 
     		{
         		message("emote", CYN + str + NOR, environment(me), ({me, target}));
         		if(environment(me)->query("broadcast"))
           			environment(me)->broadcast(CYN + str + NOR);
     		} 
     		else	return str;
   	}

   // Let NPC know we are doing emote on him.
   	if( objectp(target) ) target->relay_emote(me, verb);

   	if(if_execute == "")   return 0;
   	return 1;
}

int set_emote(string pattern, mapping def)
{
   	emote[pattern] = def;
   	save();
   	return 1;
}

int delete_emote(string pattern)
{
   	map_delete(emote, pattern);
   	save();
   	return 1;
}

mapping query_emote(string pattern)
{
   	if( !undefinedp(emote[pattern]) ) return emote[pattern];
   	else return ([]);
}

string *query_all_emote()
{
   	return keys(emote);
}

