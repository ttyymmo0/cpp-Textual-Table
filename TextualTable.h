/**
 * Created by Thomas van der Ende
 */
#pragma once
#include <vector>
#include <sstream>
#include <iomanip>

class TextualTable {
public:
	/**
	 * \brief A row of the table
	 */
	typedef std::vector< std::string > Row;

	/**
	 * \brief The table
	 */
	typedef std::vector< Row > Table;

	/**
	 * \brief Creates a new object of a table
	 * \param horizontal	The horizonal delimiter
	 * \param vertical		The vertical delimiter
	 * \param corner		The corner delimiter
	 * \param header		The horizonal delimiter
	 */
	TextualTable(char horizontal = '-', char vertical = '|', char corner = '+', bool header = true)
		: horizontal_(horizontal),
		vertical_(vertical),
		corner_(corner), total_column_width_(0) {
	}

	/**
	 * \brief Add content to the table
	 * \param content
	 */
	void add(std::string const & content) {
		current_row_.push_back(content);
	}

	/**
	 * \brief Adds the current row to the table and resets the current row it
	 */
	void end_of_row() {
		table.push_back(current_row_);
		current_row_.clear();
	}

	/**
	 * \brief Calculates the column width and stores it for the creation
	 */
	void calculate_column_width() {
		// todo: check if there are rows
		// todo: check for max row
		column_widths_ = std::vector<size_t>(table[0].size());
		// Reset the total column width
		total_column_width_ = 0;
		// calculate for each column the max width
		for (unsigned row_i = 0; row_i < table.size(); ++row_i) {
			auto row = table[row_i];
			for (unsigned column_i = 0; column_i < row.size(); ++column_i) {
				if (column_widths_.size() < column_i) {
					column_widths_[column_i] = row[column_i].size();
					break;
				}
				if (column_widths_[column_i] < row[column_i].size()) {
					column_widths_[column_i] = row[column_i].size();
				}
			}
		}
		// calculate the max width of the table
		for (auto column_width : column_widths_) {
			total_column_width_ += column_width;
		}
		total_column_width_ += column_widths_.size();
	}

	/**
	* \brief Returns a string that contains the table
	* \return table
	*/
	std::string str() {
		calculate_column_width();
		std::stringstream stream{};
		stream << ruler();
		for (unsigned row_i = 0; row_i < table.size(); ++row_i) {
			auto row = table[row_i];
			for (unsigned column_i = 0; column_i < row.size(); ++column_i) {
				auto column = row[column_i];
				stream << vertical_ << std::left << std::setw(column_widths_[column_i]) << std::setfill(' ') << column;
			}
			stream << vertical_ << "\r\n";
			if (row_i == 0) {
				stream << ruler();
			}
		}
		stream << ruler();
		return stream.str();
	}
private:
	/**
	 * \brief The horizontal delimiter
	 */
	char horizontal_;
	/**
	 * \brief The vertical delimiter
	 */
	char vertical_;
	/**
	 * \brief The corner delimiter
	 */
	char corner_;

	/**
	 * \brief Stores the max with of each column
	 */
	std::vector<size_t> column_widths_;

	/**
	 * \brief Stores the total width of the table
	 */
	int total_column_width_;

	/**
	 * \brief All the rows in the table with the columns inside
	 */
	Table table;

	/**
	 * \brief The current row of the table your building
	 */
	Row current_row_;

	/**
	 * \brief Returns a ruler for the table
	 * \return table ruler
	 */
	std::string ruler() {
		std::stringstream stream{};
		// calculate the max width of the table
		for (auto column_width : column_widths_) {
			stream << corner_ << std::setw(column_width) << std::setfill(horizontal_) << "";

		}
		stream << corner_ << "\r\n";
		return stream.str();
	}
};
