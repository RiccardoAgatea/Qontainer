#include "MeatBased.h"

/**
 * @brief      Constructor for a MeatBased subobject.
 *
 * @param[in]  t     Table that issued the order.
 * @param[in]  i     Ordered item.
 * @param[in]  w     Eventual parts of the item that must not be included in the
 *                   final dish.
 * @param[in]  temp  The temperature that the meat should be cooked at.
 */
MeatBased::MeatBased(unsigned int t,
                     const std::string &i,
                     const std::string &w,
                     const std::string &temp):
	Food(t, i, w),
	temperature(temp)
{

}

/**
 * @brief      Getter for the *temperature* field.
 *
 * @return     The value of the cooking temperature of the meat.
 */
std::string MeatBased::getTemperature() const
{
	return temperature;
}

/**
 * @brief      Reimplementation of Food::getDetails().
 *
 * @return     The concatenation of the result of Food::getDetails() followed by
 *             the string returned by getTemperature().
 */
std::vector<std::string> MeatBased::getDetails() const
{
	std::vector<std::string> aux = Food::getDetails();
	aux.push_back(getTemperature());

	return aux;
}

/**
 * @brief      Reimplementation of Food::operator==().
 *
 * @param[in]  o     Order with which __*this__ should be compared.
 *
 * @return     true if all the comparison operators between the respective
 *             fields return true and the two objects are of the same subtype of
 *             MeatBased.
 *
 *             Expands the functionality of Food::operator==() by checking for
 *             the equality in the *temperature* field.
 */
bool MeatBased::operator==(const Order &o) const
{
	return Food::operator==(o) &&
	       temperature == static_cast<const MeatBased &>(o).temperature;
}
