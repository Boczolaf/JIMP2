

#include "Scheduler.h"



academia::SchedulingItem::SchedulingItem(int course, int teacher, int room, int time, int year) {
    course_id=course;
    teacher_id=teacher;
    room_id=room;
    time_slot=time;
    this->year=year;

}

int academia::SchedulingItem::CourseId() const {
    return course_id;
}

int academia::SchedulingItem::TeacherId() const {
    return teacher_id;
}

int academia::SchedulingItem::RoomId() const {
    return room_id;
}

int academia::SchedulingItem::TimeSlot() const {
    return time_slot;
}

int academia::SchedulingItem::Year() const {
    return year;
}

academia::Schedule academia::Schedule::OfTeacher(int teacher_id) const {
    Schedule tmp;
    std::copy_if(items_.begin(),items_.end(),std::back_inserter(tmp.items_),[teacher_id](const SchedulingItem &el){return el.TeacherId()==teacher_id;});
    return tmp;
}

academia::Schedule academia::Schedule::OfRoom(int room_id) const {
    Schedule tmp;
    std::copy_if(items_.begin(),items_.end(),std::back_inserter(tmp.items_),[room_id](const SchedulingItem &el){return el.RoomId()==room_id;});
    return tmp;
}

academia::Schedule academia::Schedule::OfYear(int year) const {
    Schedule tmp;
    std::copy_if(items_.begin(),items_.end(),std::back_inserter(tmp.items_),[year](const SchedulingItem &el){return el.Year()==year;});
    return tmp;
}

std::vector<int> academia::Schedule::AvailableTimeSlots(int n_time_slots) const
{
    std::vector<int> taken, free;
    for (auto &v: items_)
    {
        taken.push_back(v.TimeSlot());
    }
    for(int i=1; i<=n_time_slots;i++)
    {
        if(std::find(taken.begin(),taken.end(),i)==taken.end())
        {
            free.push_back(i);
        }
    }
    return free;
}

void academia::Schedule::InsertScheduleItem(const SchedulingItem &item)
{
    items_.emplace_back(item);
}

size_t academia::Schedule::Size() const {
    return items_.size();
}

const academia::SchedulingItem &academia::Schedule::operator[](int id) const {
    return (items_[id]);
}

academia::Schedule academia::GreedyScheduler::PrepareNewSchedule(const std::vector<int> &rooms,
                                             const std::map<int, std::vector<int>> &teacher_courses_assignment,
                                             const std::map<int, std::set<int>> &courses_of_year,
                                             int n_time_slots)
{
    academia::Schedule output;
    for(const auto &teacher: teacher_courses_assignment)
    {
        for(auto course: teacher.second)
        {
            auto year = MatchYearToCourse(courses_of_year,course);
            auto time_and_place = TimeAndPlace(output,teacher.first,rooms,n_time_slots,year);
            output.InsertScheduleItem(SchedulingItem(course,teacher.first,time_and_place.first,time_and_place.second,year));
        }
    }
    return output;
}

int academia::GreedyScheduler::MatchYearToCourse(const std::map<int, std::set<int>> &courses_on_year, int course)const {
    for (const auto& courses: courses_on_year)
    {
        if(courses.second.find(course)!=courses.second.end())
        {
            return courses.first;
        }
    }
    throw NoViableSolutionFound();
}

std::pair<int, int> academia::GreedyScheduler::TimeAndPlace(const academia::Schedule &schedule, int teacher,
                                                  const std::vector<int> &rooms, int n_time_slots, int year) const
{
    auto teacher_free_slots = schedule.OfTeacher(teacher).AvailableTimeSlots(n_time_slots);
    auto year_free_slots = schedule.OfYear(year).AvailableTimeSlots(n_time_slots);
    std::vector<int> free_slots;
    std::set_intersection(teacher_free_slots.begin(),teacher_free_slots.end(), year_free_slots.begin(),year_free_slots.end(), std::back_inserter(free_slots));
    for (auto room: rooms)
    {
        auto room_free_slots = schedule.OfRoom(room).AvailableTimeSlots(n_time_slots);
        std::vector<int> free_slots2;
        std::set_intersection(free_slots.begin(),free_slots.end(),room_free_slots.begin(),room_free_slots.end(),std::back_inserter(free_slots2));
        if(free_slots2.size()>0)
        {
            return std::make_pair(room, *free_slots2.begin());
        }
    }

    throw NoViableSolutionFound();

}


