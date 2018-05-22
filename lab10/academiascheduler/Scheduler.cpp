

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
                                             int n_time_slots) {
    Schedule result = Schedule();
    unsigned int counter = 0;

    for(const auto &teacher : teacher_courses_assignment){
        if(teacher.second.size() >= n_time_slots) throw NoViableSolutionFound();

        for(const auto &teacher_course : teacher.second){
            for(const auto &year : courses_of_year){
                if(year.second.size() >= n_time_slots) throw NoViableSolutionFound();

                for(const auto &year_course: year.second){
                    if(teacher_course == year_course){
                        auto tmp =  SchedulingItem{teacher_course, teacher.first, rooms[counter], counter, year.first};
                        result.InsertScheduleItem(tmp);
                        ++counter;
                    }
                }
            }
        }
    }
    return result;
}

