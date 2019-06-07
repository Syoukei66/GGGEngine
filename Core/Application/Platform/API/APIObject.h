#pragma once

/*!
 * @brief プラットフォームが指定するAPIラッパーの基底クラス
 */
class GGAPIObject : public GGObject
{
public:
	virtual void SetupModules() = 0;

};