#pragma once
#include <stdexcept>
#include <string>

namespace hydrocalc
{
	/**
	* @brief Basic HR exception class
	*/
	class Exception :
		public std::runtime_error
	{
	public:
		Exception(const std::string& m)
			: std::runtime_error(m),
			type_{ "Basic" }
		{

		}
		virtual const std::string& type() const
		{
			return type_;
		};

	protected:
		std::string type_;
	};

	/**
	* @brief Exception on out of range accidents
	*/
	class ExceptionOutOfRange :
		public Exception
	{
	public:
		ExceptionOutOfRange(const std::string& m)
			: Exception(m)
		{
			type_ = "ValueOutOfRange";
		}
	};

	/**
	* @brief Exception on Re number out of range accidents
	*/
	class ExceptionReOutOfRange :
		public ExceptionOutOfRange
	{
	public:
		ExceptionReOutOfRange(const std::string& m)
			: ExceptionOutOfRange(m)
		{
			type_ = "ReOutOfRange";
		}
	};

	/**
	* @brief Exception on ReversedFlow accidents
	*/
	class ExceptionReversedFlow :
		public ExceptionOutOfRange
	{
	public:
		ExceptionReversedFlow(const std::string& m)
			: ExceptionOutOfRange(m)
		{
			type_ = "ReversedFlow";
		}
	};

	/**
	* @brief Exception on geometry parameters out of range accidents
	*/
	class ExceptionGeometryOutOfRange :
		public ExceptionOutOfRange
	{
	public:
		ExceptionGeometryOutOfRange(const std::string& m)
			: ExceptionOutOfRange(m)
		{
			type_ = "GeometryOutOfRange";
		}
	};

	/**
	* @brief Exception on non-existent functions accidents
	*/
	class ExceptionNonExistentFunction :
		public Exception
	{
	public:
		ExceptionNonExistentFunction(const std::string& m)
			: Exception(m)
		{
			type_ = "NonExistentFunction";
		}
	};

	/**
	* @brief Exception on non-existent functions accidents
	*/
	class ExceptionCompositeFunction :
		public ExceptionNonExistentFunction
	{
	public:
		ExceptionCompositeFunction(const std::string& m)
			: ExceptionNonExistentFunction(m)
		{
			type_ = "CompositeFunction";
		}
	};

	/**
	* @brief Exception invalid values
	*/
	class ExceptionInvalidValue :
		public Exception
	{
	public:
		ExceptionInvalidValue(const std::string& m)
			: Exception(m)
		{
			type_ = "InvalidValue";
		}
	};

	/**
	* @brief Exception invalid rou value
	*/
	class ExceptionInvalidRou :
		public ExceptionInvalidValue
	{
	public:
		ExceptionInvalidRou(const std::string& m)
			: ExceptionInvalidValue(m)
		{
			type_ = "InvalidRou";
		}
	};
}