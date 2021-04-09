#include <ansi.h> 
inherit SUPER_NPC;
 
void create()
{
	string *ns,name,id,*ids;
	int i;
	mapping nn;
	
	ns = ({
		"澹台","宇文","赫连","端木","夏候","澹台",
	});
	name = ns[random(sizeof(ns))];
	set("long","一个目光阴"+({"鹫","冷","森"})[random(3)]+"的胡人，面目狰狞，充满杀气。\n");
	nn = NAME_D->random_name2(0, 0, name, 0, 0);
	name = nn["name"];
	ids = nn["id"];
	ids+= ({"sha shou","sha"});
	set_name(name,ids);      
        set("gender","男性");
        set("age",17+random(20));
        set("con",30+random(10));
        set("per",10);
        set("str",30+random(10));
        set("int",15);
        set("attitude", "aggressive");
        set("bellicosity",1500);
        i = 30;
        set_level(i);
        set_skill("unarmed",i*10);
        set_skill("cuixin-zhang",i*10);
        set_skill("dodge",i*10);
        set_skill("xiaoyaoyou",i*10);
        set_skill("force",i*10);
        set_skill("ningxie-force",i*10);
        set_skill("parry",i*10);
        set_skill("blade",i*10);
        set_skill("spells",i*10);
        set_skill("dengxian-dafa",i*10);
        set_skill("wuhu-blade",i*10);
        map_skill("spells", "dengxian-dafa");
        map_skill("unarmed", "cuixin-zhang");
        map_skill("force", "ningxie-force");
        map_skill("blade", "wuhu-blade");
        map_skill("parry", "wuhu-blade");
        map_skill("dodge", "xiaoyaoyou");
	set("force_factor",300);
	set("mana_factor",300);
        set("water", 200000);
        set("food", 200000);

        set("title",HIR"拜火教"HIY"遣东使"NOR);
        set_temp("armor_level",25+random(6));
        set_temp("weapon_level",25+random(6));
        if( random(10)==6 )
        	set("env/test","HIM");
        else if( random(10)>3 )
		set("env/test",({"HIR","HIM",})[random(2)]);
        else if( random(10)==0 )
		set("env/test",({"HIB","HIR",})[random(2)]);
        else if( random(10)>1 )
		set("env/test",({"HIB","HIB","HIB","HIB","HIR",})[random(5)]);
	else	set("env/test",({"HIY","HIY","HIB","HIB","HIR",})[random(5)]);
        setup();
        carry_object(0,"cloth",1)->wear();
        carry_object(0,"shoes",1)->wear();
        carry_object(0,"waist",1)->wear();
        carry_object(0,"armor",1)->wear();
        carry_object(0,"kui",1)->wear();
        carry_object(0,"pifeng",1)->wear();
        carry_object(0,"ring",1)->wear();
        carry_object(0,"blade",1)->wield();
        powerup(0,1);
}

void die()
{
        if( !environment() || !environment()->query("mazeobj") )
	{
        	message_vision (HIR"\n$N「啪」的一声倒在地上，挣扎着抽动了几下就死了。\n\n"NOR,this_object());          
                destruct(this_object());
                return;
        }
	::die();
}

int accept_fight(object who) { return 0; }

void reward_ob(object who)
{
	object ob,xin,weapon;
	int i,wx,k;
	string str,file,*dir;

        if( !who || !userp(who) || !present(who,environment()) 
         || !environment()->query("mazeobj") 
         || !who->query_temp("maze/xiaoyan"))
        {
        	message_vision (HIR"\n$N「啪」的一声倒在地上，挣扎着抽动了几下就死了。\n\n"NOR,this_object());          
                destruct(this_object());
                return;
        }
        else
        {
        	message_vision (HIR"\n$N「啪」的一声倒在地上，挣扎着抽动了几下就死了。\n\n"NOR,this_object());      
        }
	if( !wizardp(who) && (who->query_level()>30||who->query_level()<25) )
	{
		tell_object(who,HIG"【副本】小雁塔：你在本地图得不到任何奖励。\n"NOR);
		destruct(this_object());
		return;
	}
	
	wx = 30000;
	wx = wx*4/5+random(wx/10);
	who->add("combat_exp",wx);
	tell_object(who,HIG"【副本】小雁塔：你得到了"HIR+wx+"点武学经验。\n"NOR);
		
	i = who->query_kar()+random(who->query_per());
	
	if( random(i)>=15 || wizardp(who) )
	{
		dir = ({
			"armor","cloth","hand","kui","neck",
			"pifeng","ring","shield","shoes",
			"waist","wrists",
		});	
		k = 1+random(3);
		while(k--)
		{
			file = dir[random(sizeof(dir))];
			if( file )
			{
				ob = new("/d/obj/narmor/"+file);
				ob->set("from","【小雁塔副本】");
				ob->init_armor(this_object());
				if( !ob->move(who) )
				{
					destruct(ob);
					tell_object(who,HIR"【副本】小雁塔：你的背包满了。\n"NOR);
				}
				else	tell_object(who,HIG"【副本】小雁塔：你得到了 "+ob->short()+HIG" 。\n"NOR);
			}
		}	
	}
	if( random(i)>=20 || wizardp(who) )
	{
		if( objectp(weapon=who->query_temp("weapon")) )
			file = weapon->query("skill_type");
		else	file = "unarmed";	
		dir = ({
			"axe","blade","fork","hammer","mace","spear",
			"staff","stick","sword","unarmed","whip","fork",
		});
		if( member_array(file,dir)==-1 )
			file = dir[random(sizeof(dir))];
		if( file )
		{
			ob = new("/d/obj/nweapon/"+file);
			ob->set("from","【小雁塔副本】");
			ob->init_weapon(this_object());
			if( !ob->move(who) )
			{
				destruct(ob);
				tell_object(who,HIR"【副本】小雁塔：你的背包满了。\n"NOR);
			}
			else	tell_object(who,HIG"【副本】小雁塔：你得到了 "+ob->short()+HIG" 。\n"NOR);	
		}
	}
	
	i = random(4);
	if( i>0 )
	{
		while(i--)
		{
			ob = new("/d/maze/xiaoyan-ta/obj/bangding");
			if( !ob->move(who) )
			{
				destruct(ob);
				tell_object(who,HIR"【副本】小雁塔：你的背包满了。\n"NOR);
			}
			else	
			{
				tell_object(who,HIG"【副本】小雁塔：你得到了一块"HIY"绑定用的灵石"HIG"。\n"NOR);
				CHANNEL_D->do_channel(this_object(),"rumor","听说"+who->name()+"在"HIY"【小雁塔副本】"HIM"中得到了一块"HIY"绑定石"HIM"，真叫人羡慕嫉妒恨。\n"NOR);
			}
		}
	}

	if( wizardp(who) || (who->query_level()==29 && who->query("combat_exp")>5651000) )
	{
		message_vision(HIW"\n忽见半天之中，霞光缤纷，内有一曼妙身影出现，朝$N"HIW"微微一笑。\n"NOR,who);
		if( who->query("mark/20_name") )
			message_vision(HIW"却正是以前山中惊鸿一瞥的「"HIG+who->query("mark/20_name")+"山人"HIW"」。\n"NOR,who);
		message_vision(HIW"清冷女影朝$N"HIW"一稽首：此地乃昔日吾藏书遗邸，惜被些粗鲁蝼蚁鹊巢鸠占，今得有缘人祛此人等，特送一缕神识前来相谢。\n"NOR,who);
		message_vision(HIW"女子说道：你我有缘，今就助汝一力，望汝早日步天有术，届时再细细论道。\n"NOR,who);
		message_vision(HIY"女子朝$N"HIY"打出一道道符，金光在$P头顶一闪，$N"HIY"顿时心生感悟，只觉数日来的瓶颈顿时破去！\n"NOR,who);
		if( who->level_up() )
		{
			CHANNEL_D->do_channel(this_object(),"rumor","听说"+who->name()+HIM"机缘偶得，窥破天机，境界提升了！"NOR);
			tell_object(who,HIG"【系统】你的等级提升了"HIR"1"HIG"级。\n"NOR);
			CHAR_D->setup_char( who );
			UPDATE_D->check_user(who,1);
			who->powerup(0,1);
			who->set_temp("login_data/time", time());
			who->set_temp("login_data/exp", 0);
			who->save();
		}
		message_vision(HIW"\n\n女子朝$N"HIW"微微一笑，霞光散去，已是倩影杳然。\n\n"NOR,who);
		
	}	
	
	destruct(this_object());
	return;
}

void unconcious()
{
        die();
}

void init()
{
        object me = this_player();
        
        if( !this_object()->is_fighting() 
         && userp(me) )
        {
        	if( me->query_level()<20 )
        	{
        		if( random(me->query_per())<20 )
        		{
                		this_object()->kill_ob(me);
                		this_object()->command("follow "+me->parse_command_id_list()[0]);
                	}
		}                        	
        }
        add_action("do_go","go");
}               

int do_go(string arg)
{
        if( !arg || !userp(this_player()) )
                return 0;
        if( living(this_object()) 
         && (is_fighting(this_player())||!this_object()->is_fighting()) )
                return err_msg(query("name")+"闪身将你拦住。\n");
        return 0;
}       

void kill_ob(object who)
{
	if( !who || !present(who,environment()) )
		powerup(0,1);
	::kill_ob(who);
}	
