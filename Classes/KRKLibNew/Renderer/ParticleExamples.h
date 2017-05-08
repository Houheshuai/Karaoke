#ifndef __PARTICLE_EXAMPLE_H__
#define __PARTICLE_EXAMPLE_H__

#include "Renderer/ParticleSystemQuad.h"

/** @class ParticleFire
 * @brief A fire particle system.
 */
class ParticleFire : public ParticleSystemQuad
{
public:
    /** Create a fire particle system.
     *
     * @return An autoreleased ParticleFire object.
     */
    static ParticleFire* create();
    /** Create a fire particle system withe a fixed number of particles.
     *
     * @param numberOfParticles A given number of particles.
     * @return An autoreleased ParticleFire object.
     * @js NA
     */
    static ParticleFire* createWithTotalParticles(int numberOfParticles);
    
public:
    /**
     * @js ctor
     */
    ParticleFire(){}
    /**
     * @js NA
     * @lua NA
     */
    virtual ~ParticleFire(){}

    bool init() override { return initWithTotalParticles(250); }
    virtual bool initWithTotalParticles(int numberOfParticles) override;

private:
    DISALLOW_COPY_AND_ASSIGN(ParticleFire);
};

/** @class ParticleFireworks
 * @brief A fireworks particle system.
 */
class ParticleFireworks : public ParticleSystemQuad
{
public:
    /** Create a fireworks particle system.
     *
     * @return An autoreleased ParticleFireworks object.
     */
    static ParticleFireworks* create();
    /** Create a fireworks particle system withe a fixed number of particles.
     *
     * @param numberOfParticles A given number of particles.
     * @return An autoreleased ParticleFireworks object.
     * @js NA
     */
    static ParticleFireworks* createWithTotalParticles(int numberOfParticles);
    
public:
    /**
     * @js ctor
     */
    ParticleFireworks(){}
    /**
     * @js NA
     * @lua NA
     */
    virtual ~ParticleFireworks(){}

    bool init(){ return initWithTotalParticles(1500); }
    virtual bool initWithTotalParticles(int numberOfParticles);

private:
    DISALLOW_COPY_AND_ASSIGN(ParticleFireworks);

};

/** @class ParticleSun
 * @brief A sun particle system.
 */
class ParticleSun : public ParticleSystemQuad
{
public:
    /** Create a sun particle system.
     *
     * @return An autoreleased ParticleSun object.
     */
    static ParticleSun* create();
    /** Create a sun particle system withe a fixed number of particles.
     *
     * @param numberOfParticles A given number of particles.
     * @return An autoreleased ParticleSun object.
     * @js NA
     */
    static ParticleSun* createWithTotalParticles(int numberOfParticles);
    
public:
    /**
     * @js ctor
     */
    ParticleSun(){}
    /**
     * @js NA
     * @lua NA
     */
    virtual ~ParticleSun(){}

    bool init(){ return initWithTotalParticles(350); }
    virtual bool initWithTotalParticles(int numberOfParticles);

private:
    DISALLOW_COPY_AND_ASSIGN(ParticleSun);

};

/** @class ParticleGalaxy
 * @brief A galaxy particle system.
 */
class ParticleGalaxy : public ParticleSystemQuad
{
public:
    /** Create a galaxy particle system.
     *
     * @return An autoreleased ParticleGalaxy object.
     */
    static ParticleGalaxy* create();
    /** Create a galaxy particle system withe a fixed number of particles.
     *
     * @param numberOfParticles A given number of particles.
     * @return An autoreleased ParticleGalaxy object.
     * @js NA
     */
    static ParticleGalaxy* createWithTotalParticles(int numberOfParticles);
    
public:
    /**
     * @js ctor
     */
    ParticleGalaxy(){}
    /**
     * @js NA
     * @lua NA
     */
    virtual ~ParticleGalaxy(){}

    bool init(){ return initWithTotalParticles(200); }
    virtual bool initWithTotalParticles(int numberOfParticles);

private:
    DISALLOW_COPY_AND_ASSIGN(ParticleGalaxy);

};

/** @class ParticleFlower
 * @brief A flower particle system.
 */
class ParticleFlower : public ParticleSystemQuad
{
public:
    /** Create a flower particle system.
     *
     * @return An autoreleased ParticleFlower object.
     */
    static ParticleFlower* create();
    /** Create a flower particle system withe a fixed number of particles.
     *
     * @param numberOfParticles A given number of particles.
     * @return An autoreleased ParticleFlower object.
     * @js NA
     */
    static ParticleFlower* createWithTotalParticles(int numberOfParticles);
    
public:
    /**
     * @js ctor
     */
    ParticleFlower(){}
    /**
     * @js NA
     * @lua NA
     */
    virtual ~ParticleFlower(){}

    bool init(){ return initWithTotalParticles(250); }
    virtual bool initWithTotalParticles(int numberOfParticles);

private:
    DISALLOW_COPY_AND_ASSIGN(ParticleFlower);
};

/** @class ParticleMeteor
 * @brief A meteor particle system.
 */
class ParticleMeteor : public ParticleSystemQuad
{
public:
    /** Create a meteor particle system.
     *
     * @return An autoreleased ParticleMeteor object.
     */
    static ParticleMeteor * create();
    /** Create a meteor particle system withe a fixed number of particles.
     *
     * @param numberOfParticles A given number of particles.
     * @return An autoreleased ParticleMeteor object.
     * @js NA
     */
    static ParticleMeteor* createWithTotalParticles(int numberOfParticles);
    
public:
    /**
     * @js ctor
     */
    ParticleMeteor(){}
    /**
     * @js NA
     * @lua NA
     */
    virtual ~ParticleMeteor(){}

    bool init(){ return initWithTotalParticles(150); }
    virtual bool initWithTotalParticles(int numberOfParticles);

private:
    DISALLOW_COPY_AND_ASSIGN(ParticleMeteor);
};

/** @class ParticleSpiral
 * @brief An spiral particle system.
 */
class ParticleSpiral : public ParticleSystemQuad
{
public:
    /** Create a spiral particle system.
     *
     * @return An autoreleased ParticleSpiral object.
     */
    static ParticleSpiral* create();
    /** Create a spiral particle system withe a fixed number of particles.
     *
     * @param numberOfParticles A given number of particles.
     * @return An autoreleased ParticleSpiral object.
     * @js NA
     */
    static ParticleSpiral* createWithTotalParticles(int numberOfParticles);
    
public:
    /**
     * @js ctor
     */
    ParticleSpiral(){}
    /**
     * @js NA
     * @lua NA
     */
    virtual ~ParticleSpiral(){}

    bool init(){ return initWithTotalParticles(500); }
    virtual bool initWithTotalParticles(int numberOfParticles);

private:
    DISALLOW_COPY_AND_ASSIGN(ParticleSpiral);

};

/** @class ParticleExplosion
 * @brief An explosion particle system.
 */
class ParticleExplosion : public ParticleSystemQuad
{
public:
    /** Create a explosion particle system.
     *
     * @return An autoreleased ParticleExplosion object.
     */
    static ParticleExplosion* create();
    /** Create a explosion particle system withe a fixed number of particles.
     *
     * @param numberOfParticles A given number of particles.
     * @return An autoreleased ParticleExplosion object.
     * @js NA
     */
    static ParticleExplosion* createWithTotalParticles(int numberOfParticles);
    
public:
    /**
     * @js ctor
     */
    ParticleExplosion(){}
    /**
     * @js NA
     * @lua NA
     */
    virtual ~ParticleExplosion(){}

    bool init(){ return initWithTotalParticles(700); }
    virtual bool initWithTotalParticles(int numberOfParticles);

private:
    DISALLOW_COPY_AND_ASSIGN(ParticleExplosion);
};

/** @class ParticleSmoke
 * @brief An smoke particle system.
 */
class ParticleSmoke : public ParticleSystemQuad
{
public:
    /** Create a smoke particle system.
     *
     * @return An autoreleased ParticleSmoke object.
     */
    static ParticleSmoke* create();
    /** Create a smoke particle system withe a fixed number of particles.
     *
     * @param numberOfParticles A given number of particles.
     * @return An autoreleased ParticleSmoke object.
     * @js NA
     */
    static ParticleSmoke* createWithTotalParticles(int numberOfParticles);
    
public:
    /**
     * @js ctor
     */
    ParticleSmoke(){}
    /**
     * @js NA
     * @lua NA
     */
    virtual ~ParticleSmoke(){}

    bool init(){ return initWithTotalParticles(200); }
    virtual bool initWithTotalParticles(int numberOfParticles);

private:
    DISALLOW_COPY_AND_ASSIGN(ParticleSmoke);
};

/** @class ParticleSnow
 * @brief An snow particle system.
 */
class ParticleSnow : public ParticleSystemQuad
{
public:
    /** Create a snow particle system.
     *
     * @return An autoreleased ParticleSnow object.
     */
    static ParticleSnow* create();
    /** Create a snow particle system withe a fixed number of particles.
     *
     * @param numberOfParticles A given number of particles.
     * @return An autoreleased ParticleSnow object.
     * @js NA
     */
    static ParticleSnow* createWithTotalParticles(int numberOfParticles);
    
public:
    /**
     * @js ctor
     */
    ParticleSnow(){}
    /**
     * @js NA
     * @lua NA
     */
    virtual ~ParticleSnow(){}

    bool init(){ return initWithTotalParticles(700); }
    virtual bool initWithTotalParticles(int numberOfParticles);

private:
    DISALLOW_COPY_AND_ASSIGN(ParticleSnow);
};

/** @class ParticleRain
 * @brief A rain particle system.
 */
class ParticleRain : public ParticleSystemQuad
{
public:
    /** Create a rain particle system.
     *
     * @return An autoreleased ParticleRain object.
     */
    static ParticleRain* create();
    /** Create a rain particle system withe a fixed number of particles.
     *
     * @param numberOfParticles A given number of particles.
     * @return An autoreleased ParticleRain object.
     * @js NA
     */
    static ParticleRain* createWithTotalParticles(int numberOfParticles);
    
public:
    /**
     * @js ctor
     */
    ParticleRain(){}
    /**
     * @js NA
     * @lua NA
     */
    virtual ~ParticleRain(){}

    bool init(){ return initWithTotalParticles(1000); }
    virtual bool initWithTotalParticles(int numberOfParticles);

private:
    DISALLOW_COPY_AND_ASSIGN(ParticleRain);
};

#endif //__PARTICLE_EXAMPLE_H__
