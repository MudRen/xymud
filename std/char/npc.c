// npc.c

#include <command.h>
#include <armor.h>
#define MAX_OPPENENT 4

inherit CHARACTER;
inherit F_CLEAN_UP;

nomask varargs object carry_object(string file,string type,int no_get)
{
	int w=0;
	object ob;
	if( !file && type )
	{
		file = 0;
		switch(type)
		{
			case "cloth"	:
			case TYPE_CLOTH :
			case TYPE_SKIRT : file = "cloth";break;
			case "kui"		:
			case TYPE_HEAD	: file = "kui";break;
			case "neck"		:
			case TYPE_NECK	: file = "neck";break;
			case "armor"	:
			case TYPE_ARMOR	: file = "armor";break;
			case "pifeng"	:
			case TYPE_SURCOAT: file = "pifeng";break;
			case "waist"	:
			case TYPE_WAIST	: file = "waist";break;
			case "wrists"	:
			case TYPE_WRISTS: file = "wrists";break;
			case "dun"		:
			case "shield"	:
			case TYPE_SHIELD: file = "shield";break;
			case "ring"		:
			case "finger"	:
			case TYPE_FINGER: file = "ring";break;
			case "hand"		:
			case TYPE_HANDS : file = "hand";break;
			case "shoes"	:
			case "shoe"		:
			case TYPE_BOOTS	: file = "shoes";break;
			case "axe" 		: file = "axe";w=1;break;
			case "blade" 	: file = "blade";w=1;break;
			case "fork" 	: file = "fork";w=1;break;
			case "hammer" 	: file = "hammer";w=1;break;
			case "mace" 	: file = "mace";w=1;break;
			case "spear" 	: file = "spear";w=1;break;
			case "staff" 	: file = "staff";w=1;break;
			case "stick" 	: file = "stick";w=1;break;
			case "sword" 	: file = "sword";w=1;break;
			case "unarmed" 	: file = "unarmed";w=1;break;
			case "whip" 	: file = "whip";w=1;break;
			default 		: return 0;
		}
		if( file )
		{
			if( w!=1 )
				file = "/d/obj/narmor/"+file;			
			else
				file = "/d/obj/nweapon/"+file;
			if( !objectp(ob = new(file)) ) 
				return 0;
			if( w!=1 )	
				ob->init_armor(this_object());
			else
				ob->init_weapon(this_object());	
			if( !ob->move(this_object()) )
			{
				destruct(ob);
				return 0;
			}
			if( no_get>0 )
			{
				ob->set("no_get",1);
				ob->set("value",0);
				ob->set("no_put",1);
				ob->set("no_give",1);
				ob->set("only_npc",1);
				ob->delete("class");
				ob->delete("female_only");
				ob->delete("family_name");
			}
			return ob;
		}
		return 0;
	}

	if( file->query_unique() )  {
            if(clonep()) {  // only the cloned copy can have unique item.
		if( !objectp(ob = new(file->clone_file())) ) return 0;
            } else { // master copy can't have the unique item.
                     // mon 4/5/98
                if(!file->query("replace_file") ||
                   !objectp(ob = new(file->query("replace_file")))) return 0;
            }
	}
	else
		if( !objectp(ob = new(file)) ) return 0;
		if( no_get>0 )
		{
			ob->set("no_get",1);
			ob->set("value",0);
			ob->set("no_put",1);
			ob->set("no_give",1);
		}

        ob->move(this_object());
        return ob;
}

object add_money(string type, int amount)
{
	object ob;
	string gold_dir = "/obj/money/";
	if( !type )
		return 0;
	switch(type)
	{
		case "coin" : ob = new(gold_dir+"coin");break;
		case "silver" : ob = new(gold_dir+"silver");break;
		case "gold" : ob = new(gold_dir+"gold");break;
		default : return 0;
	}
	if( amount>0 )
		ob->set_amount(amount);
	if( ob->move(this_object()) )
		return ob;
	else
	{
		if( ob ) destruct(ob);		
		return 0;
	}
}

int accept_fight(object who)
{
	string att;

	att = query("attitude");

	if( is_fighting() )	switch(att) {
		case "heroism":
			command("say 哼！出招吧！\n");
			break;
		default:
			command("say 想倚多为胜，这不是欺人太甚吗！\n");
			return 0;
	}

    if( (int)query("kee") * 100 / (int)this_object()->query_maxkee() >= 90
	&&	(int)query("sen") * 100 / (int)this_object()->query_maxsen() >= 90 ) {
		switch(att) {
			case "friendly":
				command("say " + RANK_D->query_self(this_object())
					+ "怎么可能是" + RANK_D->query_respect(who)
					+ "的对手？\n");
				return 0;
			case "aggressive":
			case "killer":
				command("say 哼！出招吧！\n");
				break;
			default:
				if( !is_fighting() )
					command("say 既然" + RANK_D->query_respect(who)
						+ "赐教，" + RANK_D->query_self(this_object())
						+ "只好奉陪。\n");
		}
		return 1;
	} else
		return 0;
}

// This function is called by the reset() of the room that creates this
// npc. When this function is called, it means the room demand the npc
// to return its startroom.
int return_home(object home)
{
	object* enemy_list;
	int i, flag=0;

	// Are we at home already?
	if( !environment()
	||	environment()==home )
		return 1;

	// Are we able to leave?
	if( !living(this_object())
	||  this_object()->query_temp("no_return") ) return 0;

	//added by mon. 7/17/97
	// modified by tool
	if( is_fighting() )  {
	   enemy_list = query_enemy();
	   for(i=0; i<sizeof(enemy_list); ++i)  {
	       if(!enemy_list[i]) continue;
	      if( sizeof(enemy_list[i]->query_enemy()) > MAX_OPPENENT )  {
             message("vision", "\n"+this_object()->name() +
             "纵身向后一跃，拱手道：阁下武艺不凡，佩服，佩服！咱们后会有期！\n\n",
             environment(), this_object());
		     enemy_list[i]->remove_killer( this_object() );
			 remove_enemy( enemy_list[i] );
			 flag = 1;
			 break;
	      }
	   }
	   if( !flag )
	      return 0;
	}

	// Leave for home now.
	message("vision", this_object()->name() + "急急忙忙地离开了。\n",
		environment(), this_object());
	return move(home);
}

// This is the chat function dispatcher. If you use function type chat
// message, you can either define your own functions or use the default
// ones.
int chat()
{
	string *msg;
	int chance, rnd;

	if( !environment() ) return 0;

	if( !chance = (int)query(is_fighting()? "chat_chance_combat": "chat_chance") )
		return 0;

	if( arrayp(msg = query(is_fighting()? "chat_msg_combat": "chat_msg"))) {
		if( random(100) < chance ) {
			rnd = random(sizeof(msg));
			if( stringp(msg[rnd]) )
				say(msg[rnd]);
			else if( functionp(msg[rnd]) )
				return evaluate(msg[rnd]);
		}
		return 1;
	}
}

// Default chat function: Let the npc random move to another room.
int random_move()
{
	mapping exits;
	string *dirs;
	int size; //added by mon 8/31/97

	if( !mapp(exits = environment()->query("exits")) ) return 0;
	dirs = keys(exits);
	size=sizeof(dirs);
	if(size>0)
	  return command("go " + dirs[random(size)]);
        else
	  return 0;
}

// Default chat function: Let the npc cast his/her enabled spells
void cast_spell(string spell)
{
	string spell_skill;
	if( this_object()->is_blind()
	 || this_object()->is_busy()
	 || this_object()->is_hunluan()
	 || time()<(this_object()->query_temp("no_cast/start")+this_object()->query_temp("no_cast/time")) )
		return;	 
	if( stringp(spell_skill = query_skill_mapped("spells")))
		SKILL_D(spell_skill)->cast_spell(this_object(), spell);
}

// Default chat function: Let the npc exert his/her enabled force
int exert_function(string func)
{
	string force_skill;
	if( this_object()->is_blind()
	 || this_object()->is_busy()
	 || this_object()->is_hunluan()
	 || time()<(this_object()->query_temp("no_exert/start")+this_object()->query_temp("no_exert/time")) )
                return 0;  
	if( stringp(force_skill = query_skill_mapped("force")))
		SKILL_D(force_skill)->exert_function(this_object(), func);
}

// Default chat function: Let the npc perform special action with 
// his/her enabled martial art
int perform_action(string skill, string action)
{
  	object weapon=this_object()->query_temp("weapon");
  	string weapon_skill,martial_skill;

	if( this_object()->is_blind()
	 || this_object()->is_busy()
	 || this_object()->is_hunluan()
	 || time()<(this_object()->query_temp("no_perform/start")+this_object()->query_temp("no_perform/time")) )
		return 0;	 

	if( !weapon ) 
		weapon_skill="unarmed";
    	else 
    	{
      		if( weapon->query("use_apply_skill") ) 
      			weapon_skill=weapon->query("apply/skill_type");
        	else	weapon_skill=weapon->query("skill_type");
    	}

	martial_skill = query_skill_mapped(skill);
	if( stringp(martial_skill) && skill==weapon_skill)
		return SKILL_D(martial_skill)->perform_action(this_object(), action);	
	return 0;		
}
