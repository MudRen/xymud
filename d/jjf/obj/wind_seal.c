#include <skill.h>
#include <ansi.h>
inherit __DIR__"seal.c";
#include <combat.h>

int random_go(object victim,string* dirs);
void doblow(object);

void create()
{
set_name("神霄风法符", ({"wind seal", "seal", "paper"}));
set_weight(100);
if(clonep())
        set_default_object(__FILE__);
else    {
        set("long","一张画上了符咒的桃符纸，中央有个大大的“风”字。\n");
        set("base_unit","张");
        set("unit", "叠");
        set("value", 0);
        set("no_put",1);
        set("no_sell",1);
        }
set_amount(1);
setup();
}

int ji_ob(object victim)
{
object seal=this_object();
object me=this_player();
object where=environment(me);
int damage, ap, dp;
        
if(me->is_busy())
        return err_msg("你正忙着呢，无法祭神霄风法符。\n");
if( !victim)
        return err_msg("你想祭的人不在这里。\n");
if( where->query("no_magic"))
        return err_msg("这里不能祭神霄风法符。\n");
if( !me->is_fighting())
        return err_msg("只有战斗中才能祭神霄风法符。\n");
if( !userp(victim))
        return err_msg("你只能将神霄风法符祭在玩家身上。\n");
if( (int)me->query("mana") < 100 )
        return err_msg("你的法力不能控制神霄风法符。\n");
if( (int)me->query("sen") < 100 )
        return err_msg("你的精神不足，很难驾驭神霄风法符。\n");

message_vision(HIC"\n$N"HIC"大喊一声“着”，手一挥，祭出了一张$n"HIC"。。。\n"NOR, me, seal);
message_vision(HIC"$n"HIC"「呼」地一下飞到半空，只见平地狂风乍起，夹头夹脑地袭向$N"HIC"。\n"NOR, victim,seal);

ap= (int)seal->query("ap");
dp= COMBAT_D->skill_power(victim,"spells",SKILL_USAGE_DEFENSE);
if ( victim->is_busy() || !living(victim) )
        dp-= dp/3;
if ( COMBAT_D->wuxing_restrain(me,victim)==1 )
        ap+= random(ap/3);      
if ( COMBAT_D->wuxing_restrain(me,victim)==-1 )
        dp+= random(dp/3);      

if( !victim->is_fighting(me) ) 
        {
        if( living(victim) ) 
                {
                if( userp(victim) ) victim->fight_ob(me);
                else    victim->kill_ob(me);
                }
        me->kill_ob(victim);
        }

if(random(ap+dp) > dp)  
        {
        message_vision(HIC"\n$N"HIC"脚下一个不稳，如断线的鹞子般飞了出去。\n"NOR,victim);
        call_out("do_blow",1,victim);
        victim->start_busy(2);
        }
else    {
        message_vision(HIC"\n谁知$N"HIC"如磐石般而立，毫不为其所动。\n"NOR,victim);
        }
me->add("mana",-50);
me->set_temp("no_cast",time());
me->set_temp("jjf_ji_seal",time());
me->set_temp("no_cast_time",5); 

if ( query_amount()>1 )  add_amount(-1);
else destruct(this_object());
return 1;
}

void do_blow(object victim)
{
string * dirs=({
        "/d/qujing/bibotan/", "/d/qujing/baotou/", "/d/qujing/baoxiang/",
        "/d/qujing/biqiu/", "/d/qujing/chechi/", "/d/qujing/dudi/", "/d/qujing/fengxian/",
        "/d/qujing/firemount/", "/d/qujing/jilei/", "/d/qujin/jindou/", "/d/qujing/jingjiling/",
        "/d/qujing/jinping/", "/d/qujing/jisaiguo/", "/d/qujing/maoying/", "/d/qujing/jisaiguo/",
        "/d/qujing/qilin/", "/d/qujing/pansi/", "/d/qujing/pingding/", "/d/qujing/qinfa/",
        "/d/qujing/qinglong/", "/d/qujing/tontian/", "/d/qujing/wudidong/", "/d/qujing/wuji/",
        "/d/qujing/xiaoxitian/", "/d/qujing/yinwu/", "/d/qujing/yuhua/", "/d/qujing/zhujie/",
        "/d/qujing/zhuzi/" 
});
random_go(victim,dirs);
destruct(this_object());
return;
}

int random_go(object victim, string* dirs)
{
int i, j, k;
object newob;
mixed *file;

if( !sizeof(dirs) )  return 1;
i = random(sizeof(dirs));    // pick up one directory
file = get_dir( dirs[i]+"*.c", -1 );
if( !sizeof(file) )             return 1;
k = sizeof(file);
while(1)  
        {
        j = random(k);
        if( file[j][1] > 0 )         break;          // pick up a file with size > 0
        }
if( (newob=load_object(dirs[i]+file[j][0])) )   
        {
        victim->move( newob ); 
        }
else    {
        random_go(victim,dirs);
        }
return 1;
}
