//【廬山聖龍】lushan-quan.c
// snowtu...20/06/03.
//meipai skill(only shengdoushi related NPCs can use it)

inherit SKILL;
#include <ansi.h>

string* skill_head =({
        "$N纵身跃起",
        "$N似退反进",
        "$$N一旋身",
        "$N忽发龙吟，使出一招",
        "$N一个筋斗翻在半空",
        "$N身形一长",
});

string* skill_tail =({
        "，双掌以排山倒海之势击向$n。",
        "，对准$n一把腰间抓了过去",
        "，双臂如铁铸一般扫向$n",
        "，双臂一阵横扫，直逼$n得连连倒退",
        "，直逼的$n节节后退。",
        "，全身劲气疾卷$n",
});

mapping *action = ({
        ([      "action":
"$N纵身跃起，一招"+HIR"「庐山爆裂拳」"NOR"，双拳化作万重幻影击向$n的$l",
                "dodge":                -40,
                "parry":                -40,
                "force":                180,
                "damage_type":          "瘀伤",
                "weapon" :              "双掌",
                "parry_msg":    "只听见「锵」一声，被$N劈手格开",
        ]),
        ([      "action":
"$N似退反进，突然欺身向前，左收右进，一招"+HIW"「庐山龙探睛」"NOR"，对准$n的$l一把刺了过去",
                "dodge":                -60,
                "parry":                -40,
                "force":                250,
                "damage_type":          "插伤",
                "weapon":               "右手食指",
                "parry_msg":    "只听见「锵」一声，被$N劈手格开",
        ]),
        ([      "action":
"只见$N一旋身，双拳舞动如风攻向$n。这一招"+HIB"「庐山龙卷风」"NOR"当真是防不胜防",
                "dodge":                -50,
                "parry":                -40,
                "force":                250,
                "damage_type":          "内伤",
                "weapon":               "双拳",
                "parry_msg":    "只听见「锵」一声，被$N劈手格开",
        ]),
        ([      "action":
"$N催动小宇宙，一招"+HIY"「庐山逆水流」"NOR"，啸声中和身而上，向$n直撞而来",
                "dodge":                -60,
                "parry":                -40,
                "force":                200,
                "damage_type":          "撞伤",
                "weapon":               "全身",
                "parry_msg":    "只听见「锵」一声，被$N劈手格开",
        ]),
            ([  "action":
"只见$N一个筋斗翻在半空，一招"+HIC"「庐山击水流」"NOR"将发未发，但是全身劲气疾卷$n",
                "dodge":                -40,
                "parry":                -20,
                "force":                250,
                "damage_type":          "内伤",
                "weapon":               "劲气",
                "parry_msg":    "只听见「锵」一声，被$N劈手格开",
        ]),
            ([  "action":
"$N身形一变，冲到$n面前就是一拳。这招"+HIG"「庐山百啸拳」"NOR"势若奔雷，气势如虹",
                "dodge":                -10,
                "parry":                -50,
                "force":                180,
                "damage_type":          "重伤",
                "weapon":               "拳头",
                "parry_msg":    "只听见「锵」一声，被$N劈手格开",
        ]),
});

int valid_learn(object me)
{
        if( (int)me->query_skill("star-force",1) < (int)me->query_skill("lushan-quan",1)/2)
                return notify_fail("你的圣斗心法还不够精湛，无法领会更深层的庐山拳法！\n");


        if( me->query_temp("weapon") || me->query_temp("secondary_weapon") )
                return notify_fail("练庐山拳法必须空手。\n");
        return 1;
}

int valid_enable(string usage)
{
        return usage=="unarmed";
}


int practice_skill(object me)
{
        if( (int)me->query_skill("star-force",1) < (int)me->query_skill("lushan-quan",1)/2)
                return notify_fail("你的圣斗心法还不够精湛，无法领会更深层的庐山拳法！\n");

        if( (int)me->query("sen") < 50)
                return notify_fail("你的精神无法集中了，休息一下再练吧。\n");

        if( (int)me->query("kee") < 50 )
                return notify_fail("你现在手足酸软，休息一下再练吧。\n");

        if( (int)me->query("force") < 20 )
                return notify_fail("你的内力不够了。\n");

        me->receive_damage("kee", 30);
        me->add("force", -20);

        return 1;
}

mapping query_action(object me, object weapon)
{
int i;
mapping* m_actions;
m_actions=me->query("skill_lushan-quan");
if( !me->query_temp("HTH_perform")) {
if(me->query("skill_lushan-quan")==0)
return action[random(6)];
if(random(2)) return action[random(6)];
return m_actions[random(sizeof(m_actions))];
}else{ return action[6];}
  return action[random(sizeof(action))];
}


string perform_action_file(string func)
{
        return CLASS_D("star") + "/lushan-quan/" + func;
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
int i = random((int)me->query_skill("lushan-quan",1)*100);
if( damage_bonus < 100 ) return 0;

if( random(damage_bonus) > victim->query_str()/20) 
        {
        victim->receive_wound("kee", damage_bonus / 2 );
        switch(random(6)) 
                {
                case 0: return HIC"$n浑身一阵爆响,已身中"+chinese_number(i)+"拳！\n"NOR;
                case 1: return HIC"$n被$N强大的小宇宙惊的目瞪口呆！已受了一击!\n"NOR;
                case 2: return HIC"只听见$n的$l「砰」地一声,已中了"+chinese_number(i)+"拳！\n"NOR;
                case 3:
                        {
                        message_vision(HIB"$N大喊一声『庐山升龙霸』一条居龙自九天而起，直飞$n！\n"NOR,me,victim);
                if(random(1)==0)
                                {
                              message_vision(HIB"\n$N被巨龙在空中顶得翻了几十个跟头！\n"NOR,victim);
                       victim->add("eff_kee",-2*victim->query("max_kee")/10);
                        victim->add("eff_sen",-2*victim->query("max_sen")/10);
                                }
                        else
                                message_vision(HIB"\n$N身型急转，不知道绕了多少圈才夺过巨龙的攻击！\n"NOR,victim);
                        }
                break;
                case 4:
                        {
                        message_vision(HIR"$N高喊一声：『庐山亢龙霸』，一条恶龙自溅底而出，尾巴向$n扫去！\n"NOR,me,victim);
                        if(random(1)==0)
                                {
                                message_vision(HIR"\n$N被恶龙的尾巴甩了个正着，$N顿时眼冒金星！\n"NOR,victim);
                       victim->add("eff_kee",-2*victim->query("max_kee")/10);
                victim->add("eff_sen",-2*victim->query("max_sen")/10);
                        }
                        else
                        message_vision(RED"$N用尽全身力气，飞升而气，恶龙的尾巴正从$N的脚底板扫过！\n"NOR,victim);
                        } 
                break;
         case 5:
                       {
                        message_vision(HIW"$N高喊一声：『庐山百龙霸』，无数只巨龙向$n冲过来！\n"NOR,me,victim);
                        if(random(1)==0)
                                {
                                message_vision(HIW"$N如一个球一样，被无数只巨龙在空中戏弄着！\n"NOR,victim);
                        victim->add("eff_kee",-3*victim->query("max_kee")/10);
                        victim->add("eff_sen",-3*victim->query("max_sen")/10);
                                }
                        else
                        message_vision(WHT"$N看准了巨龙之间的空隙，左转右转，才勉强离难！\n"NOR,victim);
                        }
                break;
                }
        }
}
void skill_improved(object me)
{
   int m_skill=me->query_skill("lushan-quan",1);

   if(m_skill>200&&m_skill%10==0){
     tell_object(me,HIW"你对庐山升龙拳的领悟加深了，你的庐山升龙拳进入了一个新的境界！\n"NOR);
     if(me->query("zichuang/times")>7){
        tell_object(me,HIW"然而你的功夫已经练至顶峰，不能再创出新招了。\n"NOR);
        return;
     }
     if(random(me->query("kar"))<20){
        tell_object(me,HIW"然而你的心中居然产生了一种失落感！\n"NOR);
        return;
     }
     if((random(me->query("int")/2)+(int)me->query_skill("literate")/50)<10){
       tell_object(me,HIW"然而你的心中升起一种惆怅的感觉，仿佛有一丝重要的东西没有抓住。\n"NOR);
       return;
     }
     tell_object(me,HIW"你突然福至心灵，对庐山升龙拳领悟出了一招新的用法！\n"NOR);
     tell_object(me,"请为这招取一个名字：");
     input_to( (: call_other, __FILE__, "name_skill", me:));
   }
   return;
}

void name_skill(object me, string arg)
{
        string *banned_name = ({
                "你", "你", "我", "他", "她", "它", "爸", "妈",
                "爷", "奶", "巫师", "天神", "神仙",
        });
   mapping* m_actions;
   mapping m_act=([]);
   int content, i=strlen(arg);
   string msg;

   m_actions=me->query("skill_lushan-quan");
   if(!pointerp(m_actions))m_actions=({});

   content=me->query("str")+me->query_skill("unarmed",1)/5;
   m_act+=(["damage":content]);
   content=-me->query("spi");
   m_act+=(["dodge" :content]);
   content=-me->query("cps");
   m_act+=(["parry" :content]);
   content=me->query("con")+me->query_skill("force",1)/2;
   m_act+=(["force" :content]);
   m_act+=(["damage_type":"瘀伤"]);
if (!arg || arg=="") 
     {
          tell_object(me,"请为你的新招式取一个名字：");
          input_to( (: call_other, __FILE__, "name_skill", me:));
          return;
     }
     else while(i--) 
     {
                if( arg[i]<=' ' ) 
                {
                        tell_object(me,"招式名字不能使用控制字元，请重新设定一个名字：");
                        input_to( (: call_other, __FILE__, "name_skill", me:));
                        return;
                }
                if(strsrch(arg, "　") >= 0) 
                {
                        tell_object(me,"招式名字不能有空格，请重新设定一个名字：");
                        input_to( (: call_other, __FILE__, "name_skill", me:));
                        return;
                }
                if(!is_chinese(arg) ) 
                {
                        tell_object(me,"请您用「中文」为你的新招式取名字：");
                        input_to( (: call_other, __FILE__, "name_skill", me:));
                        return;
                }
     }
     if( member_array(arg, banned_name)!=-1 ) 
     {
     tell_object(me,"对不起，这种名字会造成其他人的困扰。请重新设定一个名字：");
     input_to( (: call_other, __FILE__, "name_skill", me:));
     return;
     }
     if( (strlen(arg) < 4) || (strlen(arg) > 8 ) ) 
     {
     tell_object(me,"对不起，招式名字必须是 ４ 到 ８ 个中文字：");
     input_to( (: call_other, __FILE__, "name_skill", me:));
     return;
     }
//   if(!arg||arg==" ")arg="庐山升龙拳绝技"+chinese_number(sizeof(m_actions)+1);
   m_act+=(["name":arg]);
   msg= skill_head[random(sizeof(skill_head))]+BLINK+HIC"「"+arg+"」"NOR+skill_tail[random(sizeof(skill_tail))];
   m_act+=(["action":msg]);
   m_actions+=({m_act});
   me->set("skill_lushan-quan",m_actions);
   me->add("zichuang/times",1);
}



