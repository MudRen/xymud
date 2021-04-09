#include <ansi.h>
#include <condition.h>
inherit F_CLEAN_UP;

int update_condition(object me, int dur)
{
	object target,weapon;
	string t_name,t_id;
	int damage;     
	mapping hurt;
	if( !me )      
		return 0;
	hurt = me->query("weapon_hurt");
	if( !hurt || !mapp(hurt) )
	{
		me->delete_temp("death_msg");
        	return 0;
        }	
	if( dur<=1 || me->query("kee")<50 || me->query("eff_kee")<50 )
	{
		me->delete("weapon_hurt");
		me->delete_temp("death_msg");
        	return 0;
        }
	if( time()>hurt["start"]+hurt["time"] )
	{
		me->delete("weapon_hurt");
		me->delete_temp("death_msg");
        	return 0;
        }
	target = hurt["target"];
	if( !target || !objectp(target) )
        {
        	t_name = hurt["target_name"];
        	t_id = hurt["target_id"];
        }
	else    
	{
        	t_name = target->name();
        	t_id = target->parse_command_id_list()[0];
        }
        if( undefinedp(hurt["limb"]) )
		hurt["limb"] = "其他";
	switch(hurt["limb"])
        {
        	case "手" :
                	weapon = me->query_temp("weapon");
                	if( !weapon || !objectp(weapon) )
                        	weapon = me->query_temp("secondary_weapon");
                	if( !weapon || !objectp(weapon) )
                        	break;
                	if( weapon->unequip() )
                        {                       
                        	message_vision(HIR"$N"HIR"只觉得手上被"+t_name+"所创的"+hurt["type"]+"伤发作，虎口一麻，"+weapon->name()+HIR"拿捏不住，脱手摔出！\n"NOR,me);
                        	me->reset_action();
                        }
                	break;
        	case "腿" :
                	if( me->is_busy() )
                        	break;
                	me->start_busy(3);
                	tell_object(me,HIR"你只觉得腿上为"+t_name+"所创的伤口一疼，不由动作变得迟缓起来！\n"NOR);
                	break;
        	default :
                	damage = hurt["damage"];
                	if( damage<=0 ) 
                		break;
                	damage = damage/2+random(damage/2)+1;
                	message_vision("$N只觉"+hurt["limb"]+"上被"+t_name+"所创的"+hurt["type"]+"伤伤口一阵疼痛。\n",me);
                	if( !living(me) )  me->receive_damage("kee",damage,target?target:0);
                	else    me->receive_wound("kee",damage,target?target:0);
                	me->set_temp("death_msg","身中"+t_name+"("+capitalize(t_id)+")的"+hurt["type"]+"伤而死。\n");
                	break;
        }                       
	me->apply_condition("weapon_hurt",dur-1);
	return CND_CONTINUE;
}


