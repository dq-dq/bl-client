#include "Missle.h"
#include "Until.h"
#include "GameResources.h"
#include "CentralLayer.h"

Missle::Missle()
{
    sprite = NULL;
    src = NULL;
    dest = NULL;
    s = NULL;
    d = NULL;
}
Missle::~Missle()
{
    delete []s;
    delete []d;
}

Missle* Missle::newMissleClass(Unit* sc,Unit*t, int aniID,const Cmd_Missle* data)
{
    Missle* mis = new Missle();
    if (mis->init(sc,t,aniID,data)) {
        mis->autorelease();
    }else {
        delete mis;
        mis = NULL;
    }
    
	return mis;
}

bool Missle::init(Unit* sc,Unit* t,int aniID,const Cmd_Missle* data)
{
    missleData = data;
    speed = missleData->Speed;
    
    src = sc;
    dest = t;
    
    s = Missle::getp(src);
    s[1] = s[1]+src->height;
    d = Missle::getp(dest);
    
    orbit_Type_ = (Orbit_Type)missleData->Locus_type;
    
    startt = Until::millisecondNow();
    
    return true;
}

void Missle::update(float time)
{
    switch (orbit_Type_) {
        case Orbit_Type_defaultTrack:
            this->defaultTrackTM(speed);      //直线轨迹
            break;
        case Orbit_Type_Accelerate:
            this->accelerateTrackTM(3, 0.15); // 直线加速轨迹
            break;
        case Orbit_Type_ParabolaTrackNoFollow:
            this->parabolaTrackNoFollowTM(1.2, -600,3);  //炮弹移动轨迹
            break;
        case Orbit_Type_parabolaTrack:
            this->parabola(1.65, -300,2);     //箭的移动轨迹
            break;
        default:
            break;
    }
}

void Missle::onarrive()
{
    if (!soundname.empty()) {
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(soundname.c_str());
    }
    this->remove();
    this->dealDmg(dest,src,src->Damage);
}

void Missle::dealDmg(Unit* dest,Unit* src,int value)
{
    if (dest && dest->is_alive()) {
        if (dest->cmd_hurt(value)) {
            dest->_change_unit_state(UNIT_STATE_DEAD);
        }
    }
}

// ====================================================
// 魔法球的移动轨迹
// ====================================================
bool Missle::accelerateTrackTM(float speed,float a)
{
    float t = (Until::millisecondNow()-startt)*1.0f/1000 * speed;
    if (t > 1) {
        onarrive();
        return true;
    }
    t = MAX(t,0);
    t = a*t*t*t+(1.0f-a)*t;
    
    float x = Missle::inter(s[0], d[0], t);
    float y = Missle::inter(s[1], d[1], t);
    float h = Missle::inter(s[2], d[2], t);
    
    this->force_position(x, y);
    this->offsety = h;
    
    float dx = d[0] - s[0];
    float dy = d[1] - s[1];
    float dh = d[2] - s[2];
    
    sprite_->setRotation(atan2(dy + dh, dx)*180);
    return false;
}

// ====================================================
// 普通直线轨迹
// ====================================================
bool Missle::defaultTrackTM(float speed)
{
    float t = (Until::millisecondNow()-startt)*1.0f/1000 * speed;
    if (t > 1) {
        this->onarrive();
        return true;
    }
            
    float x = Missle::inter(s[0], d[0], t);
    float y = Missle::inter(s[1], d[1], t);
    float h = Missle::inter(s[2], d[2], t);
    this->force_position(x, y);
    this->offsety = h;
            
    float dx = d[0] - x;
    float dy = d[1] - y;
    float dh = d[2] - h;
            
    sprite_->setRotation(atan2(dy + dh, dx)*180);
    return false;
}

// ====================================================
// 炮弹和箭的移动轨迹
// ====================================================
bool Missle::parabola(float speed, float gravity,int rottype)
{
    float t = (Until::millisecondNow()-startt)*1.0f/1000 * speed;
	if (t > 1) {
        this->onarrive();
		return true;
    }
        
    t = MAX(t, 0);
        
    float a = gravity / 2;
    float c = s[2];
    float b = d[2] - a - c;
        
    float x = Missle::inter(s[0], d[0], t);
    float y = Missle::inter(s[1], d[1], t);
    float h = (a*t + b)*t + c;
    this->force_position(x, y);
    this->offsety = h;
        
    if (rottype == 1) {
        sprite_->setRotation(CC_RADIANS_TO_DEGREES(t*9.3));
    }else if(rottype == 2){
        float dx = d[0] - s[0];
		float dy = d[1] - s[1];
		float dh = 2*a*t + b;
		
		float r = atan2(-(dy + dh)/1.414f, dx);
		float l = sqrt(dx*dx+dy*dy+dh*dh);
		dx = dx / l;
		dy = dy / l;
		dh = dh / l;
		sprite_->setRotation(CC_RADIANS_TO_DEGREES(r));
        sprite_->setScaleX(sqrt( (dy + dh)*(dy+dh)/2 + dx*dx));
    }else {
        float dx = d[0] - s[0];
		float dy = d[1] - s[1];
		float dh = 2*a*t + b;
        
		float r = atan2((dy + dh)/1.414f, dx);
		sprite_->setRotation(CC_RADIANS_TO_DEGREES(r));
    }
    return false;
}

bool Missle::parabolaTrackNoFollowTM(float speed, float gravity, int rotatetype)
{
    this->parabola(speed, gravity, rotatetype);
    return false;
}

bool Missle::parabolaTrackTM(float speed, float gravity, int rotatetype)
{
    if (dest) {
        delete d;
        d = Missle::getp(dest);
    }
    this->parabola(speed, gravity, rotatetype);
    return false;
}