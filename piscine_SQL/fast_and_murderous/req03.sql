select justice.testimonies.person_id, justice.cases.id, justice.testimonies.content, justice.cases.description
from justice.testimonies join justice.cases
on justice.cases.id= justice.testimonies.case_id
where justice.testimonies.content like '%Nexus __%'
and justice.cases.description similar to '%(speeding|speed|fast|reckless)%';
