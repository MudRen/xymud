#include <dbase.h>
#include <name.h>
#include <ansi.h>
inherit F_EQUIP;
inherit ITEM;

void create()
{
	string msg;
	set_name("流氓兔公仔",({"gong zai","zai"}));
        set_weight(1000);
        if( clonep() ) 
        	set_default_object(__FILE__);
        else
        {		
		set("unit","个");
		set("value",100000);
		
	}
	setup();
	switch(random(5))
	{
		case 0 :
		case 9 :
		case 5 :
		case 6 :
			msg = @MSG
NORBLK                 ▂     ▂                    NOR
NORBLK               NORBLK▊NORHBWHT  NORBLK▎  NORHBWHTBLK▍ NORBLK▎      NOR
NORYEL               NORBLK▋NORHBWHT  NORHBWHTWHT NORBLK▎ NORHBWHTBLK▎NORWHT▋NOR
NORYEL               NORBLK▋NORHBWHT  NORWHT▊NORBLK▋NORHBWHT  NORHBWHTHIW NORBLK▎NOR
NORBLK               NORBLK▊NORHBWHTBLK_.-~~-._ NORBLK▍NOR
NORBLK             ◢NORHIR◢NORHBWHTHIR◣    ◢NORHIR◣NORBLK◣NOR
NORBLK             NORHIR◢NORHIR██NORHBWHTHIW●●NORHIR██NORHIR◣NOR
NORBLK           NORBLK▉ NORWHT▁▃▄▄▄▃NORBLK█ NOR
NORBLK          ◢NORWHT▅NORHBWHTBLK __--~~~~--__ NORWHT▅NORBLK◣NOR
NORBLK         NORHBWHTBLK▍ .-~            ~-.  NORBLK▍NOR
NORBLK       NORBLK▋NORHBWHTBLK  |                  |  NORBLK▍NOR
NORBLK      ▕NORHBWHTBLK▎  ~-._.---~~---._.-~   NORBLK▌NOR
NORBLK      NORBLK▊NORHBWHTBLK▏      ▁      ▁       NORWHT▊NORBLK▎NOR
NORBLK      NORBLK▊NORHBWHTBLK▎▁▄NORWHT▃▆NORHBWHTBLK      NORWHT▇▄NORHBWHTBLK▄▂ NORWHT▊NORBLK▏NORHIC一个毛茸茸的流氓兔公仔，逗得你是心花怒放。NOR
NORBLK      ▁NORHBWHTBLK◣NORWHT▅NORHBWHTBLK                 NORWHT▇▅NORHBWHTBLK◢NORBLK▁__NORHIC你可以向他许愿(wish)NOR
NORBLK  NORBLK▌NORWHT▆NORHBWHTHIR◥NORHIR◣ NORHBWHTBLK▄▂     ●   ,  ▁▃NORWHT NORHIR◢NORHBWHTHIR◤ NOR
NORHIW  NORHBWHTBLK▍NORHIR██NORHBWHTHIR◥NORBLK██ NORHBWHTBLK◣^-_  _--◢NORBLK▆NORBLK██NORHBWHTHIR◤NORHIR█NORHBWHTWHT█NORBLK▍NOR
NORBLK▌NORHBWHTWHT     NORHBWHTBLK▁ NORBLK︳██▆NORHBWHTBLK◣▔◢NORBLK▆█   ▁NORHBWHTBLK︳NORHBWHTWHT    NORWHT▌NOR
NORBLK  NORHBWHTBLK▍ NORWHT▊NORBLK▎NORHBWHTBLK▍NORBLK◣      ▆▆██  █NORWHT▋NORHBWHTBLK▎ NORHBWHTWHT█ NOR
NORBLK   NORHBWHTYEL NORHBWHTBLK▂NORBLK▏NORBLK▊NORHBWHTBLK▎NORWHT▇▆▄▃▃▃▄▅▇NORHBWHTBLK NORBLK▋ NORBLK▅▃▆NOR
NORBLK        ▕NORHBWHTBLK▍      NORHBWHTWHT            NORWHT▌NORHIW              NOR
NORBLK         NORHBWHTBLK▋                   NORWHT▋NORBLK▏  NORYEL          NOR
NORBLK NORYEL         NORHBWHTYEL NORHBWHTBLK◣     ▁▃▁     NORWHT◤NORBLK▎NOR
NORBLK           NORBLK◣▁▂▄▆▆▅▃▂◢NOR
MSG;
			break;
		default :	
				msg = @MSG
NORBLK           ◢▇▆▄▂ ▂▄▆▇NORBLK◥NOR
NORBLK           NORHBWHTBLK◤     NORWHT▇▆▇NORHBWHTBLK      NORWHT◣NOR
NORBLK         NORBLK▊NORHBWHTBLK▎      NORHBWHTWHT           NORWHT▉NORBLK▍NOR
NORBLK     __  NORBLK▋NORHBWHTBLK                    NORBLK▍ ▂▁NOR
NORBLK NORBLK▋NORWHT▅▆NORBLK▍ NORHBWHTBLK▍  ▃▅▆NORWHT NORHBWHTBLK▇▆▅▃ NORWHT▊NORREVBLK NORHBWHTBLK▍ NORWHT▊NORBLK▏NOR
NORBLK NORHBWHTBLK▍NORHBYELHIR██NORHBWHTHIW NORBLK▍NORHBWHTYEL NORHBWHTHIW NORBLK   █      ███NORHBWHTBLK▊NORWHT▌NORHBWHTHIW NORHBYELHIR██NORBLK▍NOR
NORBLK▌NORHBWHTWHT      NORWHT▆NORHBWHTHIW NORBLK︳ ██NORHBWHTBLK◤__◥NORBLK████NORHBWHTBLK︳NORHBWHTWHT     NORBLK▎NOR
NORBLK▊NORHBYELHIR██NORHBWHTHIW   NORHBWHTHIR◢NORBLK █ NORWHT◢NORHBWHTBLK.-~  ~-.NORWHT◣NORBLK▁   NORHBWHTHIR◣   NORWHT▉NORBLK▏NOR
NORBLK  NORBLK NORHBWHTBLK▃▁NORHBWHTHIR◢NORHIR◤NORWHT▄▆NORHBWHTHIW     NORHBWHTBLK●   ` NORWHT▆▄ NORHIR◥NORHBWHTHIR◣NORHBWHTBLK▁NOR
NORBLK   NORBLK▇NORBLK NORBLK▆NORWHT◢NORHBWHTBLK▅▂               ▂▅◥NORBLK▆NOR
NORBLK      NORBLK▊NORHBWHTBLK▏  NORWHT▆▄NORHBWHTBLK▄       ▄NORWHT▄▆NORHBWHTBLK  NORWHT▊NORBLK▏NOR
NORBLK      NORBLK▊NORHBWHTBLK▏    __           __    ▕NORBLK▎NOR
NORBLK        NORHBWHTBLK▍ .-~  ~--.___.--~  ~-. NORWHT▋NOR      HIC一个毛茸茸的流氓兔公仔，逗得你是心花怒放。NOR
NORBLK       NORBLK▊NORHBWHTBLK▎︳                  |▕NORBLK▎NOR     HIC你可以向他许愿(wish)NOR
NORBLK        NORBLK▋NORHBWHTBLK ~-._            _.-~  NORBLK▌ NOR
NORBLK          ◥NORHBWHTBLK▂ ---.____.---  ▃NORBLK◤NOR
NORBLK              NORHBWHTBLK▆▄▃▃▃▄▆NOR
NORBLK             NORHIR◥NORHBYELHIR█NORHBYELHIR█NORHBWHTHIW●●NORHBYELHIR██NORHIR◤NOR
NORBLK             ◥NORHIR◥NORHBWHTHIR◤    ◥NORHIR◤NORBLK◤NOR
NORBLK               NORBLK▊NORHBWHTBLK~-.__.-~ NORBLK▎NOR
NORBLK               NORBLK▋NORHBWHT  NORWHT▊NORBLK▋NORHBWHTHIW  NORWHT▊NOR
NORBLK               NORBLK▋NORHBWHTHIW NORWHT▋NOR   NORHBWHTBLK▎ NORBLK▍NOR
NORBLK               NORBLK▊NORHBWHT  NORBLK▎ NORBLK▊NORHBWHT  NORBLK▏NOR
NORBLK                 NORHICBLK▆NOR     NORHICBLK▆NOR
MSG;	
			break;
	}
	msg = COLOR_D->replace_color(msg,1);           		
	set("long",msg);
	set("armor_prop",([
		"armor" : 50+random(88),
		"dodge" : 8+random(8),
		"parry" : 8+random(8),
		"stick" : 8+random(8),
		"spells" : 8+random(8),	
		"force" : 8+random(8),	
		"axe"	: 8+random(8),	
		"blade"	:  8+random(8),	
		"hammer":  8+random(8),	
		"literate": 8+random(8),	
		"mace"	:  8+random(8),	
		"spear"	:  8+random(8),	
		"staff"	:  8+random(8),	
		"sword"	:  8+random(8),	
		"unarmed" :  8+random(8),	
		"whip"	:  8+random(8),	
		"armor_vs_force" : 88+random(888),
		"armor_vs_spells" : 88+random(888),
		"personality" : random(8),
		"intelligence": random(8),
		"improve_speed" : random(8),
	]));
	set("wear_msg","$N将$n往头上一摆，扭了扭屁股，道：祥瑞御免。\n");
	set("unequip_msg","$N小心翼翼的将$n从头上取下，放在怀中。。。。\n");	
}

void init()
{
	if( !this_player()->query("giftmark/2010shuangdan") )
		add_action("do_wish","wish");
}

int owner_pot(object me)
{
	int i,p;
	string *skills;
	mapping skill,le;
	if( !me )
		return 0;
	skill = me->query_skills();
	if( !skill || !mapp(skill) )
		return 30000;
	le = me->query_learned();	
	p = 0;
	skills = keys(skill);
	for(i=0;i<sizeof(skills)/3;i++)
		p+= (skill[skills[i]]+1)*(skill[skills[i]]+1)-le[skills[i]];
	if( p>200000 )
		p = 100000+random(100000);
	if( p<30000 )
		p = 15000+random(15000);	
	return p;
}

int do_wish()
{
	string *ww,*skills,sk;
	mapping skill;
	int p;
	int i;
	object gift,me = this_player();
	if( me->query("giftmark/2010shuangdan") )
		return 0;
	if( me->is_busy() 
	 || !present(this_object(),me) )
		return 0;	 	
	ww = ({
		"祖国早日实现统一",
		"日本早日回归祖国的怀抱",
		"韩国棒子早日回到火星",
		"我早日变成大神喜欢的漂亮妹妹",
		"小雨能坚持一百年",
	});	
	write("你虔诚的向流氓兔大神许愿：愿"+ww[random(sizeof(ww))]+"。\n");
	me->set("giftmark/2010shuangdan",1);
	write(BLINK+HIM"圣诞快乐！\n"NOR);
	me->start_busy(1);
	me->add("combat_exp",88888);
	me->add("daoxing",88888);
	write(HIY"你得到了88888点武学经验和道行。\n\n"NOR);
	p = owner_pot(me);
	me->add("balance_qn",p);
	write(BLINK+HIM"预祝元旦快乐，新年快乐，2011年更上一层楼！\n"NOR);
	write(HIY"你得到了"+p+"点潜能，已自动保存至你的潜能钱庄中。\n"NOR);
	
	skill = me->query_skills();
	if( skill && mapp(skill) )
	{
		skills = keys(skill);
		for(i=0;i<sizeof(skills)/2;i++)
		{
			sk = skills[random(sizeof(skills))];
			me->set_skill(sk,skill[sk]+1);
			write(HIC "你的「" + to_chinese(sk) + "」进步了！\n"NOR);
		}
	}
	if( ( random(100)==97 && random(me->query("age"))>14 )
	 || wizardp(me) )
	{
		gift = new("/obj/armor");
		if( gift )
		{
			if( gift->move(me) )
			{
				write(HIM"\n你福如泉涌，平白被流氓兔大神奖励了一件"+gift->query("name")+"。\n"NOR);
				me->command("touchy");
			}
			else	destruct(gift);
		}		
	}	
	me->save();
	return 1;
}