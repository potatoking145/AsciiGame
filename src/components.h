#ifndef GREENFINGERS_COMPONENTS_H_
#define GREENFINGERS_COMPONENTS_H_

struct comp_position
{
	uint8_t x;
	uint8_t y;

	template<class Archive>
	void serialize(Archive& archive)
	{
		archive(x, y);
	}
};

struct comp_last_position
{
	uint8_t x;
	uint8_t y;

	template<class Archive>
	void serialize(Archive& archive)
	{
		archive(x, y);
	}
};

struct comp_velocity
{
	int16_t x;
	int16_t y;

	template<class Archive>
	void serialize(Archive& archive)
	{
		archive(x, y);
	}
};

struct comp_char
{
	uint16_t char_code;

	template<class Archive>
	void serialize(Archive& archive)
	{
		archive(char_code);
	}
};

#endif