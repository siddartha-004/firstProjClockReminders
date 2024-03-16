<h3>Individuals often face difficulty in managing their schedules and keep track of important events,tasks,deadlines.This is scalable and robust reminder solution that allow to schedule unlimited reminders.</h3><br>

Concepts used:linked list,stack using linked list
Flow chart of program:
<img width="552" alt="image" src="https://github.com/siddartha-004/firstProjClockReminders/assets/113697558/438109a5-7e25-471c-b6ff-709f1998e3c4">
Results:
<img width="603" alt="image" src="https://github.com/siddartha-004/firstProjClockReminders/assets/113697558/4fcfb6bd-bc0d-4d8e-86ee-add13e1263fc">
<img width="598" alt="image" src="https://github.com/siddartha-004/firstProjClockReminders/assets/113697558/89b3c079-05a5-48d0-84c0-d824db85e94a">
<img width="587" alt="image" src="https://github.com/siddartha-004/firstProjClockReminders/assets/113697558/2ea74e17-3cec-4617-b3a4-17e669971181">
<img width="588" alt="image" src="https://github.com/siddartha-004/firstProjClockReminders/assets/113697558/760cf0b3-ab45-443a-a241-0a76f57daded">
<img width="566" alt="image" src="https://github.com/siddartha-004/firstProjClockReminders/assets/113697558/0822825c-d23b-41ee-af04-75b932cf4b6a">

<p>Description of each module</p>
<h3>Push function for adding new remainder</h3>
<p>1.new node is created that contain info of dn,mn,yn,th,tm,label(date,time)</p>
<p>2.If list is empty , the new node becomes both the first and last node in the list. </p>
<p>3.If the list is not empty, the code traverses through the list to find the correct position to insert the new node. It compares the date and time components of the new node with those of existing nodes to maintain the sorted order.Once the correct position is found, the new node is inserted before the node pointed to by place.</p>
<p>4.If place is pointing to the first node, nn becomes the new first node.Otherwise, nn is inserted between place and place->next.</p>
<p>5.After insertion, if the last node's next pointer points to nn, it means nn is now the last node, so last is updated to point to nn.Finally, the function returns a pointer to the newly inserted node nn.</p>


