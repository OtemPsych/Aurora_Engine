#include <fstream>
#include <functional>
#include <iostream>

#include "Animation.h"

namespace au
{
	Animation::Animation(Animation::Data* data, SpriteNode* node)
		: data_(data)
		, node_(node)
		, current_rect_(0)
		, elapsed_time_(sf::Time::Zero)
		, animation_ongoing_(false)
	{
		activateUpdating(ActivationTarget::All, false);
	}

	Animation::Animation(const std::string& data_file, const std::string& sprite_file,
		                 Animation::Data* data, SpriteNode* node)
		: data_(data)
		, node_(node)
		, current_rect_(0)
		, elapsed_time_(sf::Time::Zero)
		, animation_ongoing_(false)
	{
		activateUpdating(ActivationTarget::All, false);
		parseJsonFile(data_file, sprite_file);
	}

	void Animation::start()
	{
		activateUpdating(ActivationTarget::Current, true);
	}

	void Animation::stop()
	{
		activateUpdating(ActivationTarget::Current, false);
	}

	void Animation::restart()
	{
		current_rect_ = 0;
		elapsed_time_ = sf::Time::Zero;
		activateUpdating(ActivationTarget::Current, true);
		animation_ongoing_ = true;
	}

	void Animation::parseJsonFile(const std::string& data_file, const std::string& sprite_file)
	{
		std::ifstream fin(data_file, std::ios::in);
		if (fin.is_open()) {
			unsigned sprite_index = 1;
			while (!fin.eof()) {
				fin.seekg(0);
				std::string str_needed(sprite_file + std::to_string(sprite_index++) + ".png");
				std::string str_read;

				// Find filename
				do {
					std::getline(fin, str_read);
				} while (str_read.find(str_needed) == std::string::npos && !fin.eof());
				if (fin.eof())
					break;

				// Find frame
				std::getline(fin, str_read);
				fin.seekg(static_cast<size_t>(fin.tellg()) - (str_read.length() + 1));

				// Find rect start
				sf::FloatRect rect;
				char ch;
				do {
					fin.get(ch);
				} while (ch != '{');

				// Find values
				std::function<std::string()> findNextValue([&fin]() -> std::string {
					std::string value("");
					char ch;
					do {
						fin.get(ch);
					} while (ch != ':');

					while (true) {
						fin.get(ch);
						if (ch != ',' && ch != '}')
							value += ch;
						else
							break;
					}

					return value;
				});

				rect.left = std::stof(findNextValue());
				rect.top = std::stof(findNextValue());
				rect.width = std::stof(findNextValue());
				rect.height = std::stof(findNextValue());

				// Find pivot
				for (int i = 0; i < 6; i++)
					std::getline(fin, str_read);
				fin.seekg(static_cast<size_t>(fin.tellg()) - (str_read.length() + 1));

				// Find origin start
				sf::Vector2f origin;
				do {
					fin.get(ch);
				} while (ch != '{');

				// Find values
				origin.x = std::stof(findNextValue());
				origin.y = std::stof(findNextValue());

				data_->frames.emplace_back();
				data_->frames.back().texture_rect = rect;
				data_->frames.back().origin = origin;
			}

			if (data_->frames.empty())
				std::cerr << "Unable to read file " << data_file << " using sprite file " << sprite_file << "\n";
			fin.close();
			finalizeAnimationSetup();
		}
		else
			std::cerr << "Unable to open file: " << data_file << std::endl;
	}

	void Animation::updateNodeProperties()
	{
		node_->setTextureRect(data_->frames[current_rect_].texture_rect);

		const sf::FloatRect node_lbounds(node_->getLocalBounds());
		const sf::Vector2f& node_origin = data_->frames[current_rect_].origin;
		node_->setOrigin(node_origin.x * node_lbounds.width,
			             node_origin.y * node_lbounds.height);
	}

	void Animation::finalizeAnimationSetup()
	{
		// Loopback animation (if needed)
		if (data_->loopback)
			for (int i = data_->frames.size() - 2; i >= 0; --i)
				data_->frames.push_back(data_->frames[i]);

		// Calculate time per frame
		const sf::Time frame_duration(sf::seconds(data_->total_duration.asSeconds() / data_->frames.size()));
		for (auto& frame : data_->frames)
			frame.duration = frame_duration;

		updateNodeProperties();
	}

	void Animation::updateCurrent(sf::Time dt)
	{
		const bool reached_end = !(current_rect_ < data_->frames.size() - 1 || data_->repeat);

		if (animation_ongoing_ && !reached_end && (elapsed_time_ += dt) >= data_->frames[current_rect_].duration) {
			if (!reached_end || data_->repeat) {
				updateNodeProperties();
				elapsed_time_ = sf::Time::Zero;

				if (data_->repeat) {
					if (current_rect_ < data_->frames.size() - 1)
						current_rect_++;
					else
						current_rect_ = 0;
				}
				else
					current_rect_++;
			}
			else
				animation_ongoing_ = false;
		}
	}
}