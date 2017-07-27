// �����棬ʱ�临�Ӷ� O(n)���ռ临�Ӷ� O(1)
class Solution
{
public:
	ListNode *reverseKGroup(ListNode *head, int k)
	{
		if (head == nullptr || head->next == nullptr || k < 2)
			return head;
		ListNode dummy(-1);
		dummy.next = head;
		for (ListNode *prev = &dummy, *end = head; end; end = prev->next)
		{
			for (int i = 1; i < k && end; i++)
				end = end->next;
			if (end == nullptr)
				break;
			prev = reverse(prev, prev->next, end);
		}
		return dummy.next;
	}
};