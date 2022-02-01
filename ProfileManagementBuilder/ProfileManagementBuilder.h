#pragma once

#ifndef EAE6320_PROFILEMANAGEMENTBUILDER_H
#define EAE6320_PROFILEMANAGEMENTBUILDER_H

// Includes
//=========

#include <Tools/AssetBuildLibrary/iBuilder.h>

// Class Declaration
//==================

namespace eae6320
{
	namespace Assets
	{
		class ProfileManagementBuilder final : public iBuilder
		{
			// Inherited Implementation
			//=========================

		private:

			// Build
			//------

			cResult Build(const std::vector<std::string>& i_arguments) final;

			//cResult Build();

		};
	}
}

#endif	// EAE6320_PROFILEMANAGEMENTBUILDER_H