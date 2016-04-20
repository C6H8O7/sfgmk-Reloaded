#include "stdafx.h"

namespace gmk
{
	namespace net
	{
		Address::Address()
			: Address("0.0.0.0", 0)
		{

		}

		Address::Address(r_string _ip, r_uint16 _port)
			: m_address(CreateAddress(_ip, _port))
		{

		}

		Address::Address(const Address& _cpy)
		{
			m_address = _cpy.m_address;
		}

		Address::~Address()
		{

		}

		sockaddr_in Address::getAddress()
		{
			return m_address;
		}

		sockaddr_in* Address::getAddressPtr()
		{
			return &m_address;
		}

		r_int32 Address::getAddressSize()
		{
			return m_addressSize;
		}

		r_int32* Address::getAddressSizePtr()
		{
			return &m_addressSize;
		}

		r_bool Address::isValid()
		{
			return m_address.sin_addr.S_un.S_addr > 0;
		}

		sockaddr_in Address::CreateAddress(r_string _address, r_uint16 _port)
		{
			sockaddr_in addr;
			memset(&addr, 0, sizeof(addr));

			addr.sin_addr.S_un.S_addr = inet_addr(_address.c_str());
			addr.sin_family = AF_INET;
			addr.sin_port = htons(_port);

			return addr;
		}

		r_bool Address::operator== (Address& _cmp)
		{
			return (m_address.sin_port == _cmp.m_address.sin_port && m_address.sin_addr.S_un.S_addr == _cmp.m_address.sin_addr.S_un.S_addr);
		}

		r_int8* Address::c_str()
		{
			return inet_ntoa(m_address.sin_addr);
		}
	}
}