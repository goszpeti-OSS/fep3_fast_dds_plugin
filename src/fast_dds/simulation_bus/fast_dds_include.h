

#pragma once

#pragma warning( push )
#pragma warning( disable : 4245 )

#include <fastcdr/Cdr.h>

#include <fastrtps/attributes/ParticipantAttributes.h>
#include <fastrtps/attributes/PublisherAttributes.h>
#include <fastrtps/attributes/SubscriberAttributes.h>

#include <fastdds/rtps/exceptions/Exception.h>
#include <fastrtps/subscriber/SampleInfo.h>
#include <fastrtps/rtps/common/Types.h>

#include <fastrtps/types/TypeIdentifier.h>
#include <fastrtps/types/TypeObject.h>

#include <fastdds/dds/builtin/common/Types.hpp>
#include <fastdds/dds/builtin/topic/ParticipantBuiltinTopicData.hpp>

#include <fastdds/dds/core/condition/GuardCondition.hpp>
#include <fastdds/dds/core/condition/WaitSet.hpp>
#include <fastdds/dds/core/condition/StatusCondition.hpp>
#include <fastdds/dds/core/condition/Condition.hpp>

#include <fastdds/dds/core/LoanableCollection.hpp>
#include <fastdds/dds/core/policy/QosPolicies.hpp>
#include <fastdds/dds/core/policy/ParameterTypes.hpp>
#include <fastdds/dds/core/policy/ReaderDataLifecycleQosPolicy.hpp>
#include <fastdds/dds/core/policy/WriterDataLifecycleQosPolicy.hpp>
#include <fastdds/dds/core/status/StatusMask.hpp>
#include <fastdds/dds/core/UserAllocatedSequence.hpp>
#include <fastdds/dds/core/StackAllocatedSequence.hpp>

#include <fastrtps/types/DynamicDataHelper.hpp>
#include <fastrtps/types/DynamicDataFactory.h>

#include <fastdds/dds/domain/DomainParticipant.hpp>
#include <fastdds/dds/domain/DomainParticipantListener.hpp>
#include <fastdds/dds/domain/DomainParticipantFactory.hpp>

#include <fastdds/dds/topic/TypeSupport.hpp>
#include <fastdds/dds/topic/TopicDataType.hpp>
#include <fastdds/dds/topic/TopicDescription.hpp>
#include <fastdds/dds/topic/TopicListener.hpp>
#include <fastdds/dds/topic/Topic.hpp>

#include <fastdds/dds/publisher/DataWriterListener.hpp>
#include <fastdds/dds/publisher/PublisherListener.hpp>
#include <fastdds/dds/publisher/Publisher.hpp>
#include <fastdds/dds/publisher/qos/PublisherQos.hpp>
#include <fastdds/dds/publisher/DataWriter.hpp>
#include <fastdds/dds/publisher/qos/DataWriterQos.hpp>

 #include <fastdds/dds/subscriber/SubscriberListener.hpp>
 #include <fastdds/dds/subscriber/Subscriber.hpp>
 #include <fastdds/dds/subscriber/DataReader.hpp>
 #include <fastdds/dds/subscriber/DataReaderListener.hpp>
#include <fastdds/dds/subscriber/SampleState.hpp>
#include <fastdds/dds/subscriber/ViewState.hpp>
#include <fastdds/dds/subscriber/InstanceState.hpp>


 #include <fastdds/dds/subscriber/qos/DataReaderQos.hpp>
 #include <fastdds/dds/subscriber/qos/ReaderQos.hpp>
#include <fastdds/dds/subscriber/qos/SubscriberQos.hpp>

 #include "../types/stream_types.h"
 #include "../types/stream_typesPubSubTypes.h"
using namespace eprosima::fastdds::dds;
#undef logError
#undef logWarning
#undef logInfo

#pragma warning( pop )
