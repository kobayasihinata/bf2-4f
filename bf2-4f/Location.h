#pragma once

typedef struct Location
{
	float x;
	float y;

	Location operator +(Location location)
	{
		Location ret;

		ret.x = this->x + location.x;
		ret.y = this->y + location.y;

		return ret;
	}

	Location operator -(Location location)
	{
		Location ret;

		ret.x = this->x - location.x;
		ret.y = this->y - location.y;

		return ret;
	}

	Location operator *(Location location)
	{
		Location ret;

		ret.x = this->x * location.x;
		ret.y = this->y * location.y;

		return ret;
	}

	Location operator /(Location location)
	{
		Location ret;

		ret.x = this->x / location.x;
		ret.y = this->y / location.y;

		return ret;
	}

	Location operator =(Location location)
	{
		this->x = location.x;
		this->y = location.y;

		return *this;
	}


	bool operator==(Location location)
	{
		bool ret = (this->x == location.x && this->y == location.y);
		return ret;
	}

	bool operator!=(Location location)
	{
		bool ret = (this->x != location.x || this->y != location.y);
		return ret;
	}

};