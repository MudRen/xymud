inherit __DIR__"n2.c"; 
      
void setname() 
{
set_name("观音菩萨", ({ "guanyin pusa", "guanyin", "pusa" }));
set("title", "救苦救难大慈大悲");
set("long", @LONG
理圆四德，智满金身。眉如小月，眼似双星。兰心欣紫竹，
蕙性爱得藤。她就是落伽山上慈悲主，潮音洞里活观音。
LONG);
set("gender", "女性");
set("age", 35);
set("attitude", "peaceful");
set("rank_info/self", "贫僧");
set("rank_info/respect", "菩萨娘娘");
set("class", "bonze");
set("str",24);
set("per",100);//means no rong-mao description.
set("int", 100);
set("con", 100);
set("str", 100);
create_family("南海普陀山",2, "菩萨");
set("chushi/chushi_putuo","yes");        
set("class", "bonze");
set("skill_mark/putuo_jinguzhou",1);  //紧箍咒

set_skill("jienan-zhi", 850);
set_skill("lotusmove", 850);
set_skill("staff", 850);
set_skill("lunhui-zhang", 850);
set_skill("lotusforce", 850);
set_skill("literate", 800);
set_skill("buddhism", 850);
set_skill("blade", 850);
set_skill("cibeidao", 850);
set_skill("dodge", 850);
set_skill("force", 850);
set_skill("spells", 850);
set_skill("parry", 850);

map_skill("blade","cibeidao");
map_skill("spells", "buddhism");
map_skill("force", "lotusforce");
map_skill("unarmed", "jienan-zhi");
map_skill("staff", "lunhui-zhang");
map_skill("parry", "lunhui-zhang");
map_skill("dodge", "lotusmove");
}

void setup()
{
::setup();  
carry_object(0,"staff",1)->wield();   
set("combat_exp",105000000);
set("daoxing",20000000);
}

int is_job(){return 1;}