//Cracked by snowtu
inherit NPC;
#include <ansi.h>

mapping clr = ([
        "BLK"   : NOR BLK"黑"NOR"色",
        "RED"   : NOR RED"红"NOR"色",
        "GRN"   : NOR GRN"绿"NOR"色",
        "YEL"   : NOR YEL"土"NOR"色",
        "BLU"   : NOR BLU"蓝"NOR"色",
        "MAG"   : NOR MAG"紫"NOR"色",
        "CYN"   : NOR CYN"青"NOR"色",
        "WHT"   : NOR WHT"白"NOR"色",
        "HIR"   : NOR HIR"红"NOR"色",
        "HIG"   : NOR HIG"绿"NOR"色",
        "HIY"   : NOR HIY"黄"NOR"色",
        "HIB"   : NOR HIB"蓝"NOR"色",
        "HIM"   : NOR HIM"粉"NOR"色",
        "HIW"   : NOR HIW"白"NOR"色",
        "NOR"   : NOR HIR"取消"NOR,
]);     

string to_color()
{
int i;  
string *strs,str = "";
object me = this_player();
if ( !me || !living(me) )
        return 0;
if ( !me->query_temp("ask_name_color") )
        {
        str+= "这个颜色功能只限于公共频道时你的说话内容，你可以设置以下颜色："NOR;
        strs = keys(clr);
        for(i=0;i<sizeof(strs);i++)
                {
                if ( i%3==0 )
                        str+= "\n";
        str+= sprintf("\t%s : %s",strs[i],clr[strs[i]]);
                }
        me->set_temp("ask_name_color",1); 
        str+= "\n要设置这些颜色，你得保证你身上带有一千两黄金，并且钱庄内有九千两黄金的存款。\n";
        return str;
        }
return "既然你已决定了，那就直接输入你想要的颜色吧，命令格式：namecolor <你想要的颜色>，例如 namecolor HIW\n";
}

void create()
{
set_name("长孙无忌", ({"zhangsun wuji","minister","wuji","zhangsun"}));
set("long","开国名臣，时任户部尚书，你如果有黄金万两，可以在他这里更改你的姓名(rename)。\n");
set_level(23);
set("gender", "男性");
set("title","户部尚书");
set("age", 50);
set("attitude", "friendly");
set("combat_exp", 250000);
set("per", 30);
set("inquiry",([
        "颜色" : (: to_color :),
]));    
setup();
carry_object("/d/gao/obj/changpao")->wear();
}

void init()
{
add_action("do_rename", "rename");
add_action("do_ncolor","namecolor");
this_player()->delete_temp("wuji_rename");
}

int err_msg(string arg)
{
write(arg);
return 1;
}       

int do_ncolor(string arg)
{
int i;
object *inv,gold,me = this_player();
if ( !arg )
        return 0;
if ( !me->query_temp("ask_name_color") )
        return 0;
if ( member_array(arg,keys(clr))==-1 )
        {
        me->delete_temp("ask_name_color");
        return err_msg("命令格式错误。\n");
        }       
if ( arg=="NOR" )
        {
        me->delete_temp("ask_name_color");
        me->delete("name_color");
        me->save();
        return err_msg("你取消了自己的名字颜色\n");
        }                       
if(!me->check_balance(90000000) )
        return err_msg("你的钱庄存款不足9000两黄金。\n");
inv = all_inventory(me);
for(i=0;i<sizeof(inv);i++)
        {
        if ( inv[i]->query("id")!="gold"
          || inv[i]->query("money_id")!="gold" )
                continue;
          gold = inv[i];
        }
if ( !gold )
        return err_msg("你没有携带黄金。\n");
if ( gold->query_amount()<1000 )
        return err_msg("你携带的黄金不足千两。\n");
gold->add_amount(-1000);
me->add("balance",-90000000);
me->set("name_color",arg);
me->delete_temp("ask_name_color");
me->save();
write("好了，你将自己的名字颜色设成了"+clr[arg]+"。\n");
return 1;
}

int do_rename(string arg)
{
object me = this_player();
        
if ( !arg )     return err_msg("你准备改成什么名字？\n");
if ( !me->check_balance(90000000) )
        return err_msg("你的钱庄帐户不足9000两黄金，没有资格改名字哦。\n");
if ( !me->query_temp("wuji_rename") )
        return err_msg(name()+"说道：你先得缴两千两黄金作为手续费。\n");
arg = CONVERT_D->input(arg,me);
if ( !LOGIN_D->check_legal_name(arg) ) 
        return err_msg("你输入的名字不合法!请重新输入!\n");
message_vision("$N朝$n点了点头，拿出一份卷宗写了几笔。\n",this_object(),me);
CHANNEL_D->do_channel(this_object(),"rumor","听说"HIR+me->name(1)+HIM"将自己的名字在户部更改为了"HIR+arg+HIM"。");
me->balance_add(-80000000);
me->set("name",arg);
me->save();
write("你的名字更改完毕。\n所需八千两黄金已从你钱庄帐户上自动扣除。\n");
me->delete_temp("wuji_rename");
return 1;
}

int accept_money(object who,int v)
{
if ( v>=20000000 )
        {
        if ( !who->check_balance(90000000) )
                {
                tell_object(who,name()+"朝你摇了摇头，说道：你钱庄帐户不足九千两黄金，我没法子帮你改名字。\n");
                return 0;
                }
        tell_object(who,name()+"朝你点了点头，说道：你可以更改你的名字(rename)，没更改前
最好别离开，否则这两千两黄金算是上缴国库了。\n");
        who->set_temp("wuji_rename",1);
        return 1;
        }
return 0;
}  

