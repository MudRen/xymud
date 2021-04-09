inherit __DIR__"n.c";

string *names = ({
        "风","虚","清","华","子","德",
        "道","李","庄","扬",
});

void setname()
{
object ob,*obs; 
string name;    
int i;
i = sizeof(names);
name = "";
while(strlen(name)/2<2+random(2))
        name+= names[random(i)];
set_name(name,({"di zi", "dizi",}));
set("age", 16+random(20));
set("class", "taoist");
set("per", 26);
set("long", "方寸弟子。\n");
set("int", 30);
set_skill("literate", 400+random(350)); 
set_skill("unarmed", 400+random(350)); 
set_skill("dodge", 400+random(350)); 
set_skill("force", 400+random(350)); 
set_skill("parry", 400+random(350)); 
set_skill("stick", 400+random(350)); 
set_skill("spells", 400+random(350)); 
set_skill("whip", 400+random(350)); 
set_skill("dao", 400+random(350)); 
set_skill("puti-zhi", 400+random(350)); 
set_skill("wuxiangforce", 400+random(350)); 
set_skill("qianjun-bang", 400+random(350)); 
set_skill("jindouyun", 400+random(350)); 
map_skill("spells", "dao");
map_skill("unarmed", "puti-zhi");
map_skill("force", "wuxiangforce");
map_skill("stick", "qianjun-bang");
map_skill("parry", "qianjun-bang");
map_skill("dodge", "jindouyun");
map_skill("sword", "liangyi-sword");
create_family("方寸山三星洞", 2+random(3), "弟子");
}

void setup()
{
::setup();
carry_object("/d/city/npc/obj/cloth")->wear();
carry_object("/d/city/npc/obj/shoes")->wear();
carry_object("/d/city/npc/obj/armor")->wear();
carry_object("/d/city/npc/obj/pifeng")->wear();
carry_object("/d/city/npc/obj/kui")->wear();
carry_object("/d/obj/suburb/que")->wear();
carry_object("/d/city/npc/obj/stick")->wield();
set("combat_exp",60000000);
set("daoxing",6000000);
}

