#include <ansi.h>; 
inherit SKILL;

void beast_hurt(object me, object victim, object weapon, int damage);

mapping *action = ({
        ([
                "action": "$N将尾巴往$n的$l用力一甩",
                "damage": 100,
                "dodge" : -30,
                "parry" : 10,
                "damage_type": "抽伤",
                "weapon_name": "尾巴",
                "post_action":  (: call_other, __FILE__, "beast_hurt" :),             
        ]),
        ([
                "action": "$N扑上来张嘴往$n的$l狠狠地一咬",
                "damage": 60,
                "dodge" : -5,
                "parry" : -5,   
                "damage_type":  "咬伤",
                "post_action":  (: call_other, __FILE__, "beast_hurt" :),             
        ]),
        ([
                "action": "$N用爪子往$n的$l一拍",
                "damage": 100,
                "force" : 10,
                "dodge" : 15,
                "parry" : -10,  
                "damage_type":  "砸伤",
                "weapon_name":  "爪子",
                "post_action":  (: call_other, __FILE__, "beast_hurt" :),
        ]),
        ([
                "action": "$N用嘴往$n的$l一啄",
                "damage": 50,
                "dodge" : -10,
                "parry" : -10,  
                "damage_type":  "刺伤",
                "weapon_name":  "尖嘴", 
                "post_action":  (: call_other, __FILE__, "beast_hurt" :),             
        ]),
});

int valid_learn(object me)
{
        return 0;
}

int valid_enable(string usage)
{
        return usage=="unarmed";
}

mapping query_action(object me, object weapon)
{
        switch(this_player()->query("type"))
        {
                case "snake": return action[1];
                case "bird" : return action[3];
                case "bear" : return action[2];
                default : return action[1];
        }
}

int practice_skill(object me)
{
        return 0;
}

string perform_action_file(string func) 
{ 
             return CLASS_D("12gong") + "/beast-hurt/" + func; 
} 

void beast_hurt(object me, object victim, object weapon, int damage)
{
        if( !me || !victim || !me->is_fighting(victim) )
                return;
        if( damage<=0 )
                return;
        if( !me->query("type") )
                return;
        switch(me->query("type"))
        {
                case "snake" :
                        if( !victim->query_condition("snake_poison") )
                                victim->apply_condition("snake_poison",200);
                        break;
                case "bird" :
                        if( !victim->query_condition("eyeill") )
                                victim->apply_condition("eyeill",200);
                        break;
                default :
                        if( !victim->query_condition("beast_hurt") )
                                victim->apply_condition("beast_hurt",200);
                        break;
        }               
}
