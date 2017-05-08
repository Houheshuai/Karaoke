#ifndef _KARAOKE_PAINT_H
#define _KARAOKE_PAINT_H

class KaraokePaintingBrush
{
public:
	virtual ~KaraokePaintingBrush(){};
	virtual void Update(void *) = 0;
	virtual void Draw(void *) = 0;
	virtual void Reset() = 0;
};

#endif